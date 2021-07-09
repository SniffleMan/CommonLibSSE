#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class ExtraOutfitItem : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraOutfitItem;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kOutfitItem;

		~ExtraOutfitItem() override;  // 00

		// override (BSExtraData)
		[[nodiscard]] ExtraDataType GetType() const override;  // 01 - { return kOutfitItem; }

		// members
		FormID        id;     // 10 - BGSOutfit
		std::uint32_t pad14;  // 14
	};
	static_assert(sizeof(ExtraOutfitItem) == 0x18);
}
