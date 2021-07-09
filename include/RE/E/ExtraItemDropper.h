#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class ExtraItemDropper : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraItemDropper;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kItemDropper;

		~ExtraItemDropper() override;  // 00

		// override (BSExtraData)
		[[nodiscard]] ExtraDataType GetType() const override;  // 01 - { return kItemDropper; }

		// members
		ObjectRefHandle dropper;  // 10
		std::uint32_t   pad14;    // 14
	};
	static_assert(sizeof(ExtraItemDropper) == 0x18);
}
