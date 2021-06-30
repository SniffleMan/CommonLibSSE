#pragma once

#include "RE/N/NiBinaryStream.h"

namespace RE
{
	class NiFile : public NiBinaryStream
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiFile;

		enum class OpenMode
		{
			kReadOnly = 0,
			kWriteOnly = 1,
			kAppendOnly = 2
		};

		~NiFile() override;  // 00

		// override (NiBinaryStream)
		bool good() const override;                    // 01 - { return isGood; }
		void seek(std::int32_t a_numBytes) override;   // 02
		void get_info(BufferInfo& a_buf) override;     // 04
		void set_endian_swap(bool a_doSwap) override;  // 05

		// add
		virtual void          seek(std::int32_t a_offset, std::int32_t a_from);  // 06
		[[nodiscard]] virtual std::uint32_t size() const;                                      // 07

		// members
		std::uint32_t                             bufferAllocSize;  // 20
		std::uint32_t                             bufferReadSize;   // 24
		std::uint32_t                             pos;              // 28
		std::uint32_t                             pad2C;            // 2C
		char*                                     buffer;           // 30
		std::FILE*                                file;             // 38
		stl::enumeration<OpenMode, std::uint32_t> mode;             // 40
		bool                                      isGood;           // 44
		std::uint8_t                              pad45;            // 45
		std::uint16_t                             pad46;            // 46
	};
	static_assert(sizeof(NiFile) == 0x48);
}
