#pragma once

#include "RE/E/ExtraDataTypes.h"
#include "RE/E/ExtraLight.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class NiRefObject;

	class ExtraMagicLight : public ExtraLight
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraMagicLight;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kMagicLight;

		~ExtraMagicLight() override;  // 00

		// override (BSExtraData)
		[[nodiscard]] ExtraDataType GetType() const override;  // 01 - { return kMagicLight; }
	};
	static_assert(sizeof(ExtraMagicLight) == 0x18);
}
