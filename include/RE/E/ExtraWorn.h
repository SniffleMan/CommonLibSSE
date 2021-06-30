#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class ExtraWorn : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraWorn;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kWorn;

		~ExtraWorn() override;  // 00

		// override (BSExtraData)
		[[nodiscard]] ExtraDataType GetType() const override;  // 01 - { return kWorn; }
	};
	static_assert(sizeof(ExtraWorn) == 0x10);
}
