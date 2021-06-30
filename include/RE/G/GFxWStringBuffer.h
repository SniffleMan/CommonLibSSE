#pragma once

namespace RE
{
	class GFxWStringBuffer
	{
	public:
		using value_type = wchar_t;
		using size_type = UPInt;
		using reference = value_type&;
		using const_reference = const value_type&;

		struct ReserveHeader
		{
			ReserveHeader();
			ReserveHeader(const ReserveHeader& a_rhs);
			ReserveHeader(ReserveHeader&& a_rhs);
			ReserveHeader(wchar_t* a_buffer, UPInt a_size);
			~ReserveHeader() = default;

			ReserveHeader& operator=(const ReserveHeader& a_rhs);
			ReserveHeader& operator=(ReserveHeader&& a_rhs);

			// members
			wchar_t* buffer;  // 00
			UPInt    size;    // 08
		};
		static_assert(sizeof(ReserveHeader) == 0x10);

		template <std::uint32_t SIZE>
		struct Reserve : public ReserveHeader
		{
			Reserve() :
				ReserveHeader(buffer, SIZE)
			{}

			// members
			wchar_t buffer[SIZE];  // 10
		};

		// (constructor)
		GFxWStringBuffer();
		GFxWStringBuffer(const GFxWStringBuffer& a_rhs);
		GFxWStringBuffer(GFxWStringBuffer&& a_rhs);
		GFxWStringBuffer(const ReserveHeader& a_reserve);
		GFxWStringBuffer(ReserveHeader&& a_reserve);

		// (destructor)
		~GFxWStringBuffer();

		// operator=
		GFxWStringBuffer& operator=(const GFxWStringBuffer& a_rhs);
		GFxWStringBuffer& operator=(GFxWStringBuffer&& a_rhs);
		GFxWStringBuffer& operator=(const wchar_t* a_rhs);
		GFxWStringBuffer& operator=(const std::wstring_view& a_rhs);

		// element access
		reference       operator[](size_type a_pos);
		const_reference operator[](size_type a_pos) const;

		wchar_t&       front();
		[[nodiscard]] const wchar_t& front() const;

		wchar_t&       back();
		[[nodiscard]] const wchar_t& back() const;

		[[nodiscard]] const wchar_t* data() const noexcept;
		wchar_t*       data() noexcept;

		[[nodiscard]] const wchar_t* c_str() const noexcept;

		operator std::wstring_view() const noexcept;

		// Capacity
		[[nodiscard]] bool empty() const noexcept;

		[[nodiscard]] size_type size() const noexcept;

		[[nodiscard]] size_type length() const noexcept;

		// Operations
		void clear() noexcept;

		void resize(size_type a_count);

	protected:
		wchar_t* alloc(size_type a_count);
		void     release();

		// members
		wchar_t*      _text;      // 00
		UPInt         _length;    // 08
		ReserveHeader _reserved;  // 10
	};
	static_assert(sizeof(GFxWStringBuffer) == 0x20);
}
