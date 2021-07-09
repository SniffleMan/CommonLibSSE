#pragma once

namespace RE
{
	class GStringBuffer;

	class GString
	{
	public:
		using value_type = char;  // can also be wchar_t
		using size_type = UPInt;
		using reference = value_type&;
		using const_reference = const value_type&;

		enum class HeapType
		{
			kGlobal = 0,   // Global
			kLocal = 1,    // Address-based
			kDynamic = 2,  // Part of class
			kMask = 3
		};

		struct FlagConstants
		{
			enum FlagConstant : UPInt
			{
				kReserveIsSizeShift = static_cast<UPInt>((sizeof(UPInt) * 8 - 1))  // indicates reserve == size
			};
		};
		using FlagConstant = FlagConstants::FlagConstant;

		struct DataDesc
		{
#pragma warning(push)
#pragma warning(disable: 4293)  // '<<': shift count negative or too big, undefined behavior
			enum : UPInt
			{
				kFullFlag = static_cast<UPInt>(1 << FlagConstant::kReserveIsSizeShift)
			};
#pragma warning(pop)

			DataDesc();
			~DataDesc();

			void  AddRef();
			void  Release();
			[[nodiscard]] UPInt GetCapacity() const;
			[[nodiscard]] bool  IsFull() const;
			void  SetFull(bool a_set);

			// members
			UPInt                 capacity;  // 00
			volatile std::int32_t refCount;  // 08
			char                  data[1];   // 0C
		};
		static_assert(sizeof(DataDesc) == 0x10);

		union DataDescUnion
		{
			DataDescUnion();

			DataDesc*                         data;
			stl::enumeration<HeapType, UPInt> heapType;
		};
		static_assert(sizeof(DataDescUnion) == 0x8);

		// (constructor)
		GString();
		GString(const GString& a_rhs);
		GString(GString&& a_rhs);
		GString(const char* a_rhs);
		GString(const std::string_view& a_rhs);

		// (destructor)
		~GString();

		// operator=
		GString& operator=(const GString& a_rhs);
		GString& operator=(GString&& a_rhs);
		GString& operator=(const char* a_rhs);
		GString& operator=(const std::string_view& a_rhs);

		// element access
		reference       operator[](size_type a_pos);
		const_reference operator[](size_type a_pos) const;

		char&       front();
		[[nodiscard]] const char& front() const;

		char&       back();
		[[nodiscard]] const char& back() const;

		[[nodiscard]] const char* data() const noexcept;
		char*       data() noexcept;

		[[nodiscard]] const char* c_str() const noexcept;

		operator std::string_view() const noexcept;

		// Capacity
		[[nodiscard]] bool empty() const noexcept;

		[[nodiscard]] size_type size() const noexcept;

		[[nodiscard]] size_type length() const noexcept;

		// Operations
		void clear() noexcept;

		inline friend bool operator==(const GString& a_lhs, const char* a_rhs) { return (a_lhs.data() == a_rhs || std::strcmp(a_lhs.data(), a_rhs) == 0); }
		inline friend bool operator!=(const GString& a_lhs, const char* a_rhs) { return !(a_lhs == a_rhs); }
		inline friend bool operator==(const char* a_lhs, const GString& a_rhs) { return a_rhs == a_lhs; }
		inline friend bool operator!=(const char* a_lhs, const GString& a_rhs) { return !(a_lhs == a_rhs); }
		inline friend bool operator==(const GString& a_lhs, const GString& a_rhs) { return a_lhs == a_rhs.c_str(); }
		inline friend bool operator!=(const GString& a_lhs, const GString& a_rhs) { return !(a_lhs == a_rhs); }
		inline friend bool operator==(const GString& a_lhs, const std::string_view& a_rhs) { return a_lhs == a_rhs.data(); }
		inline friend bool operator!=(const GString& a_lhs, const std::string_view& a_rhs) { return !(a_lhs == a_rhs); }
		inline friend bool operator==(const std::string_view& a_lhs, const GString& a_rhs) { return a_rhs == a_lhs; }
		inline friend bool operator!=(const std::string_view& a_lhs, const GString& a_rhs) { return !(a_lhs == a_rhs); }

		static UPInt BernsteinHashFunction(const void* a_dataIn, UPInt a_size, UPInt a_seed = 5381);

	protected:
		GString*  ctor(const char* a_str);
		[[nodiscard]] HeapType  heap_type() const;
		[[nodiscard]] DataDesc* get_desc() const;
		void      set_desc(DataDesc* a_desc);

		// members
		DataDescUnion _dataDesc;  // 0
	};
	static_assert(sizeof(GString) == 0x8);
}
