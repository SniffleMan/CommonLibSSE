#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/B/BSTArray.h"
#include "RE/E/ExtraDataTypes.h"
#include "RE/F/FormTypes.h"

namespace RE
{
	class ExtraPromotedRef : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraPromotedRef;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kPromotedRef;

		~ExtraPromotedRef() override;  // 00

		// override (BSExtraData)
		[[nodiscard]] ExtraDataType GetType() const override;  // 01 - { return kPromotedRef };

		// members
		BSTArray<TESForm*> promotedRefOwners;  // 10
	};
	static_assert(sizeof(ExtraPromotedRef) == 0x28);
}
