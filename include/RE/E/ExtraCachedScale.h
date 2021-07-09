#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class ExtraCachedScale : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraCachedScale;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kCachedScale;

		~ExtraCachedScale() override;  // 00

		// override (BSExtraData)
		[[nodiscard]] ExtraDataType GetType() const override;  // 01 - { return kCachedScale; }

		// members
		float scale3D;   // 10
		float refScale;  // 10
	};
	static_assert(sizeof(ExtraCachedScale) == 0x18);
}
