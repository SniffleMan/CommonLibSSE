#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class ExtraLeveledItem : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraLeveledItem;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kLeveledItem;

		~ExtraLeveledItem() override;  // 00

		// override (BSExtraData)
		[[nodiscard]] ExtraDataType GetType() const override;  // 01 - { return kLeveledItem; }

		// members
		FormID        levItem;  // 10
		std::uint32_t pad14;    // 14
	};
	static_assert(sizeof(ExtraLeveledItem) == 0x18);
}
