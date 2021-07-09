#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class ExtraRefractionProperty : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraRefractionProperty;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kRefractionProperty;

		~ExtraRefractionProperty() override;  // 00

		// override (BSExtraData)
		[[nodiscard]] ExtraDataType GetType() const override;  // 01 - { return kRefractionProperty; }

		// members
		float         refractionPower;  // 10
		std::uint32_t unk14;            // 14
	};
	static_assert(sizeof(ExtraRefractionProperty) == 0x18);
}
