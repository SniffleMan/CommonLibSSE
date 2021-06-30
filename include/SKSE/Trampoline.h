#pragma once

#if defined(SKSE_SUPPORT_XBYAK)
namespace Xbyak
{
	class CodeGenerator;
}
#endif

namespace SKSE
{
	namespace detail
	{
		[[nodiscard]] constexpr std::size_t roundup(std::size_t a_number, std::size_t a_multiple) noexcept
		{
			if (a_multiple == 0) {
				return 0;
			}

			const auto remainder = a_number % a_multiple;
			return remainder == 0 ?
                       a_number :
                       a_number + a_multiple - remainder;
		}

		[[nodiscard]] constexpr std::size_t rounddown(std::size_t a_number, std::size_t a_multiple) noexcept
		{
			if (a_multiple == 0) {
				return 0;
			}

			const auto remainder = a_number % a_multiple;
			return remainder == 0 ?
                       a_number :
                       a_number - remainder;
		}
	}

	class Trampoline
	{
	public:
		using deleter_type = std::function<void(void* a_mem, std::size_t a_size)>;

		Trampoline() = default;
		Trampoline(const Trampoline&) = delete;

		Trampoline(Trampoline&& a_rhs) { move_from(std::move(a_rhs)); }

		explicit Trampoline(std::string_view a_name) :
			_name(a_name)
		{}

		~Trampoline() { release(); }

		Trampoline& operator=(const Trampoline&) = delete;

		Trampoline& operator=(Trampoline&& a_rhs)
		{
			if (this != std::addressof(a_rhs)) {
				move_from(std::move(a_rhs));
			}
			return *this;
		}

		void create(std::size_t a_size) { return create(a_size, nullptr); }

		void create(std::size_t a_size, void* a_module)
		{
			if (a_size == 0) {
				stl::report_and_fail("cannot create a trampoline with a zero size"sv);
			}

			if (!a_module) {
				const auto text = REL::Module::get().segment(REL::Segment::textx);
				a_module = text.pointer<std::byte>() + text.size();
			}

			auto mem = do_create(a_size, reinterpret_cast<std::uintptr_t>(a_module));
			if (!mem) {
				stl::report_and_fail("failed to create trampoline"sv);
			}

			set_trampoline(mem, a_size,
				[](void* a_mem, std::size_t) {
					WinAPI::VirtualFree(a_mem, 0, WinAPI::MEM_RELEASE);
				});
		}

		void set_trampoline(void* a_trampoline, std::size_t a_size) { set_trampoline(a_trampoline, a_size, {}); }

		void set_trampoline(void* a_trampoline, std::size_t a_size, deleter_type a_deleter)
		{
			auto trampoline = static_cast<std::byte*>(a_trampoline);
			if (trampoline) {
				constexpr auto INT3 = static_cast<int>(0xCC);
				std::memset(trampoline, INT3, a_size);
			}

			release();

			_deleter = std::move(a_deleter);
			_data = trampoline;
			_capacity = a_size;
			_size = 0;

			log_stats();
		}

		[[nodiscard]] void* allocate(std::size_t a_size)
		{
			auto result = do_allocate(a_size);
			log_stats();
			return result;
		}

#ifdef SKSE_SUPPORT_XBYAK
		[[nodiscard]] void* allocate(Xbyak::CodeGenerator& a_code);
#endif

		template <class T>
		[[nodiscard]] T* allocate()
		{
			return static_cast<T*>(allocate(sizeof(T)));
		}

		[[nodiscard]] constexpr std::size_t empty() const noexcept { return _capacity == 0; }
		[[nodiscard]] constexpr std::size_t capacity() const noexcept { return _capacity; }
		[[nodiscard]] constexpr std::size_t allocated_size() const noexcept { return _size; }
		[[nodiscard]] constexpr std::size_t free_size() const noexcept { return _capacity - _size; }

		template <std::size_t N>
		std::uintptr_t write_branch(std::uintptr_t a_src, std::uintptr_t a_dst)
		{
			std::uint8_t data = 0;
			if constexpr (N == 5) {
				// E9 cd
				// JMP rel32
				data = 0xE9;
			} else if constexpr (N == 6) {
				// FF /4
				// JMP r/m64
				data = 0x25;
			} else {
				static_assert(false && N, "invalid branch size");
			}

			return write_branch<N>(a_src, a_dst, data);
		}

		template <std::size_t N, class F>
		std::uintptr_t write_branch(std::uintptr_t a_src, F a_dst)
		{
			return write_branch<N>(a_src, stl::unrestricted_cast<std::uintptr_t>(a_dst));
		}

		template <std::size_t N>
		std::uintptr_t write_call(std::uintptr_t a_src, std::uintptr_t a_dst)
		{
			std::uint8_t data = 0;
			if constexpr (N == 5) {
				// E8 cd
				// CALL rel32
				data = 0xE8;
			} else if constexpr (N == 6) {
				// FF /2
				// CALL r/m64
				data = 0x15;
			} else {
				static_assert(false && N, "invalid call size");
			}

			return write_branch<N>(a_src, a_dst, data);
		}

		template <std::size_t N, class F>
		std::uintptr_t write_call(std::uintptr_t a_src, F a_dst)
		{
			return write_call<N>(a_src, stl::unrestricted_cast<std::uintptr_t>(a_dst));
		}

	private:
		[[nodiscard]] void* do_create(std::size_t a_size, std::uintptr_t a_address);

		[[nodiscard]] void* do_allocate(std::size_t a_size)
		{
			if (a_size > free_size()) {
				stl::report_and_fail("Failed to handle allocation request"sv);
			}

			auto mem = _data + _size;
			_size += a_size;

			return mem;
		}

		void write_5branch(std::uintptr_t a_src, std::uintptr_t a_dst, std::uint8_t a_opcode)
		{
#pragma pack(push, 1)
			struct SrcAssembly
			{
				// jmp/call [rip + imm32]
				std::uint8_t opcode;  // 0 - 0xE9/0xE8
				std::int32_t disp;    // 1
			};
			static_assert(offsetof(SrcAssembly, opcode) == 0x0);
			static_assert(offsetof(SrcAssembly, disp) == 0x1);
			static_assert(sizeof(SrcAssembly) == 0x5);

			// FF /4
			// JMP r/m64
			struct TrampolineAssembly
			{
				// jmp [rip]
				std::uint8_t  jmp;    // 0 - 0xFF
				std::uint8_t  modrm;  // 1 - 0x25
				std::int32_t  disp;   // 2 - 0x00000000
				std::uint64_t addr;   // 6 - [rip]
			};
			static_assert(offsetof(TrampolineAssembly, jmp) == 0x0);
			static_assert(offsetof(TrampolineAssembly, modrm) == 0x1);
			static_assert(offsetof(TrampolineAssembly, disp) == 0x2);
			static_assert(offsetof(TrampolineAssembly, addr) == 0x6);
			static_assert(sizeof(TrampolineAssembly) == 0xE);
#pragma pack(pop)

			TrampolineAssembly* mem = nullptr;
			if (const auto it = _5branches.find(a_dst); it != _5branches.end()) {
				mem = reinterpret_cast<TrampolineAssembly*>(it->second);
			} else {
				mem = allocate<TrampolineAssembly>();
				_5branches.emplace(a_dst, reinterpret_cast<std::byte*>(mem));
			}

			const auto disp =
				reinterpret_cast<const std::byte*>(mem) -
				reinterpret_cast<const std::byte*>(a_src + sizeof(SrcAssembly));
			if (!in_range(disp)) {  // the trampoline should already be in range, so this should never happen
				stl::report_and_fail("displacement is out of range"sv);
			}

			SrcAssembly assembly;
			assembly.opcode = a_opcode;
			assembly.disp = static_cast<std::int32_t>(disp);
			REL::safe_write(a_src, &assembly, sizeof(assembly));

			mem->jmp = static_cast<std::uint8_t>(0xFF);
			mem->modrm = static_cast<std::uint8_t>(0x25);
			mem->disp = static_cast<std::int32_t>(0);
			mem->addr = static_cast<std::uint64_t>(a_dst);
		}

		void write_6branch(std::uintptr_t a_src, std::uintptr_t a_dst, std::uint8_t a_modrm)
		{
#pragma pack(push, 1)
			struct Assembly
			{
				// jmp/call [rip + imm32]
				std::uint8_t opcode;  // 0 - 0xFF
				std::uint8_t modrm;   // 1 - 0x25/0x15
				std::int32_t disp;    // 2
			};
			static_assert(offsetof(Assembly, opcode) == 0x0);
			static_assert(offsetof(Assembly, modrm) == 0x1);
			static_assert(offsetof(Assembly, disp) == 0x2);
			static_assert(sizeof(Assembly) == 0x6);
#pragma pack(pop)

			std::uintptr_t* mem = nullptr;
			if (const auto it = _6branches.find(a_dst); it != _6branches.end()) {
				mem = reinterpret_cast<std::uintptr_t*>(it->second);
			} else {
				mem = allocate<std::uintptr_t>();
				_6branches.emplace(a_dst, reinterpret_cast<std::byte*>(mem));
			}

			const auto disp =
				reinterpret_cast<const std::byte*>(mem) -
				reinterpret_cast<const std::byte*>(a_src + sizeof(Assembly));
			if (!in_range(disp)) {  // the trampoline should already be in range, so this should never happen
				stl::report_and_fail("displacement is out of range"sv);
			}

			Assembly assembly;
			assembly.opcode = static_cast<std::uint8_t>(0xFF);
			assembly.modrm = a_modrm;
			assembly.disp = static_cast<std::int32_t>(disp);
			REL::safe_write(a_src, &assembly, sizeof(assembly));

			*mem = a_dst;
		}

		template <std::size_t N>
		[[nodiscard]] std::uintptr_t write_branch(std::uintptr_t a_src, std::uintptr_t a_dst, std::uint8_t a_data)
		{
			const auto disp = reinterpret_cast<std::int32_t*>(a_src + N - 4);
			const auto nextOp = a_src + N;
			const auto func = nextOp + *disp;

			if constexpr (N == 5) {
				write_5branch(a_src, a_dst, a_data);
			} else if constexpr (N == 6) {
				write_6branch(a_src, a_dst, a_data);
			} else {
				static_assert(false && N, "invalid branch size");
			}

			return func;
		}

		void move_from(Trampoline&& a_rhs)
		{
			_5branches = std::move(a_rhs._5branches);
			_6branches = std::move(a_rhs._6branches);
			_name = std::move(a_rhs._name);

			_deleter = std::move(a_rhs._deleter);

			_data = a_rhs._data;
			a_rhs._data = nullptr;

			_capacity = a_rhs._capacity;
			a_rhs._capacity = 0;

			_size = a_rhs._size;
			a_rhs._size = 0;
		}

		void log_stats() const;

		[[nodiscard]] bool in_range(std::ptrdiff_t a_disp) const
		{
			constexpr auto min = std::numeric_limits<std::int32_t>::min();
			constexpr auto max = std::numeric_limits<std::int32_t>::max();

			return min <= a_disp && a_disp <= max;
		}

		void release()
		{
			if (_data && _deleter) {
				_deleter(_data, _capacity);
			}

			_5branches.clear();
			_6branches.clear();
			_data = nullptr;
			_capacity = 0;
			_size = 0;
		}

		std::map<std::uintptr_t, std::byte*> _5branches;
		std::map<std::uintptr_t, std::byte*> _6branches;
		std::string                          _name{ "Default Trampoline"sv };
		deleter_type                         _deleter;
		std::byte*                           _data{ nullptr };
		std::size_t                          _capacity{ 0 };
		std::size_t                          _size{ 0 };
	};
}
