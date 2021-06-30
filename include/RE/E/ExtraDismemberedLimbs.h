#pragma once

#include "RE/B/BGSBodyPartDefs.h"
#include "RE/B/BSExtraData.h"
#include "RE/B/BSFixedString.h"
#include "RE/B/BSTArray.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class TESForm;

	struct DismemberedLimb
	{
		BSTArray<TESForm*>                                         objects;  // 00
		stl::enumeration<BGSBodyPartDefs::LIMB_ENUM, std::uint8_t> limb;     // 18
		bool                                                       unk19;    // 19
		bool                                                       unk1A;    // 1A
		std::uint8_t                                               pad1B;    // 1B
		std::uint32_t                                              pad1C;    // 1C
	};
	static_assert(sizeof(DismemberedLimb) == 0x20);

	class ExtraDismemberedLimbs : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraDismemberedLimbs;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kDismemberedLimbs;

		~ExtraDismemberedLimbs() override;  // 00

		// override (BSExtraData)
		[[nodiscard]] ExtraDataType GetType() const override;  // 01 - { return kDismemberedLimbs; }

		// members
		std::uint16_t                                               limbs;             // 10
		bool                                                        eaten;             // 12
		std::uint8_t                                                unk13;             // 13
		std::uint32_t                                               unk14;             // 14
		TESForm*                                                    deathObject;       // 18
		BSTArray<DismemberedLimb*>                                  dismemberedLimbs;  // 20
		stl::enumeration<BGSBodyPartDefs::LIMB_ENUM, std::uint32_t> lastHitLimb;       // 38
		std::uint32_t                                               pad3C;             // 3C
	};
	static_assert(sizeof(ExtraDismemberedLimbs) == 0x40);
}
