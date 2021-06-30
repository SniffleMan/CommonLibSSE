#pragma once

namespace RE
{
	class NiBinaryStream
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiBinaryStream;

		using int_type = std::int32_t;
		using pos_type = std::uint32_t;
		using off_type = std::int32_t;

		struct BufferInfo
		{
		public:
			// members
			void*         buffer;           // 00
			std::uint32_t totalSize;        // 08
			std::uint32_t bufferAllocSize;  // 0C
			std::uint32_t bufferReadSize;   // 10
			std::uint32_t bufferPos;        // 14
			std::uint32_t streamPos;        // 18
			std::uint32_t pad1C;            // 1C
		};
		static_assert(sizeof(BufferInfo) == 0x20);

		NiBinaryStream();
		virtual ~NiBinaryStream();  // 00

		// add
		[[nodiscard]] virtual bool          good() const = 0;                    // 01
		virtual void          seek(std::int32_t a_numBytes) = 0;   // 02
		[[nodiscard]] virtual std::uint32_t tell() const;                        // 03 - { return _absoluteCurrentPos; }
		virtual void          get_info(BufferInfo& a_buf);         // 04
		virtual void          set_endian_swap(bool a_doSwap) = 0;  // 05

		template <class CharT>
		bool get(CharT& a_ch);
		template <class CharT>
		bool read(CharT* a_str, std::uint32_t a_count);
		template <class CharT>
		bool put(CharT a_ch);
		template <class CharT>
		bool write(const CharT* a_str, std::uint32_t a_count);

	protected:
		using ReadFn = std::uint32_t(NiBinaryStream* a_this, void* a_buffer, std::uint32_t a_bytes, std::uint32_t* a_componentSizes, std::uint32_t a_numComponents);
		using WriteFn = std::uint32_t(NiBinaryStream* a_this, const void* a_buffer, std::uint32_t a_bytes, std::uint32_t* a_componentSizes, std::uint32_t a_numComponents);

		std::uint32_t binary_read(void* a_buffer, std::uint32_t a_totalBytes, std::uint32_t* a_componentSizes, std::uint32_t a_numComponents = 1);
		std::uint32_t binary_write(const void* a_buffer, std::uint32_t a_totalBytes, std::uint32_t* a_componentSizes, std::uint32_t a_numComponents = 1);

		// members
		std::uint32_t _absoluteCurrentPos;  // 08
		std::uint32_t _pad0C;               // 0C
		ReadFn*       _readFn;              // 10
		WriteFn*      _writeFn;             // 18
	};
	static_assert(sizeof(NiBinaryStream) == 0x20);

	template <class CharT>
	inline bool NiBinaryStream::get(CharT& a_ch)
	{
		return read(&a_ch, 1);
	}

	template <class CharT>
	inline bool NiBinaryStream::read(CharT* a_str, std::uint32_t a_count)
	{
		std::uint32_t size = sizeof(CharT);
		std::uint32_t toRead = a_count * size;
		std::uint32_t bytesRead = binary_read(a_str, toRead, &size);
		return bytesRead == toRead;
	}

	template <class CharT>
	inline bool NiBinaryStream::put(CharT a_ch)
	{
		return write(&a_ch, 1);
	}

	template <class CharT>
	inline bool NiBinaryStream::write(const CharT* a_str, std::uint32_t a_count)
	{
		std::uint32_t size = sizeof(CharT);
		std::uint32_t toWrite = a_count * size;
		std::uint32_t bytesWritten = binary_write(a_str, toWrite, &size);
		return bytesWritten == toWrite;
	}
}

namespace std
{
	template <class CharT, class Traits, class Allocator>
	inline bool getline(RE::NiBinaryStream& a_input, std::basic_string<CharT, Traits, Allocator>& a_str)
	{
		CharT delim = std::use_facet<std::ctype<CharT>>(std::locale()).widen('\n');
		return getline(a_input, a_str, delim);
	}

	template <class CharT, class Traits, class Allocator>
	inline bool getline(RE::NiBinaryStream& a_input, std::basic_string<CharT, Traits, Allocator>& a_str, CharT a_delim)
	{
		a_str.erase();
		CharT c;
		auto  notEOF = a_input.get(c);
		if (notEOF) {
			do {
				if (!std::char_traits<CharT>::eq(c, a_delim)) {
					a_str.push_back(c);
				} else {
					break;
				}

				if (a_str.size() != a_str.max_size()) {
					notEOF = a_input.get(c);
				} else {
					break;
				}
			} while (notEOF);
			return true;
		} else {
			return false;
		}
	}
}
