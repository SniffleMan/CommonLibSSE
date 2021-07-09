#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class NiLight;

	struct REFR_LIGHT
	{
		NiPointer<NiLight> light;       // 00
		float              wantDimmer;  // 08
		std::uint32_t      pad0C;       // 0C
	};
	static_assert(sizeof(REFR_LIGHT) == 0x10);

	class ExtraLight : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraLight;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kLight;

		~ExtraLight() override;  // 00

		// override (BSExtraData)
		[[nodiscard]] ExtraDataType GetType() const override;  // 01 - { return kLight; }

		// members
		REFR_LIGHT* lightData;  // 10
	};
	static_assert(sizeof(ExtraLight) == 0x18);
}
