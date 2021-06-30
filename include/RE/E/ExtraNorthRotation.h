#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class ExtraNorthRotation : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraNorthRotation;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kNorthRotation;

		~ExtraNorthRotation() override;  // 00

		// override (BSExtraData)
		[[nodiscard]] ExtraDataType GetType() const override;  // 01 - { return kNorthRotation; }

		// members
		float         northRot;  // 10
		std::uint32_t pad14;     // 14
	};
	static_assert(sizeof(ExtraNorthRotation) == 0x18);
}
