#pragma once

#include "RE/B/BSISoundDescriptor.h"

namespace RE
{
	class BGSSoundCategory;
	class TESFile;
	class TESForm;

	class BGSSoundDescriptor : public BSISoundDescriptor
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSSoundDescriptor;

		~BGSSoundDescriptor() override;  // 00

		// add
		virtual void          InitSound(TESForm* a_src);  // 03
		virtual bool          LoadSound(TESFile* a_mod);  // 04
		[[nodiscard]] virtual std::uint32_t GetType() const = 0;        // 05 - CRC hash of class name
		virtual void          Unk_06(void) = 0;           // 06

		// members
		BGSSoundCategory* category;              // 08 - GNAM
		FormID            alternateSoundFormID;  // 10 - SNAM
		std::uint32_t     pad14;                 // 14
	};
	static_assert(sizeof(BGSSoundDescriptor) == 0x18);
}
