#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"
#include "RE/M/MagicCaster.h"

namespace RE
{
	class ExtraMagicCaster :
		public BSExtraData,  // 00
		public MagicCaster   // 10
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraMagicCaster;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kMagicCaster;

		~ExtraMagicCaster() override;  // 00

		// override (BSExtraData)
		[[nodiscard]] ExtraDataType GetType() const override;  // 01 - { return kMagicCaster; }
	};
	static_assert(sizeof(ExtraMagicCaster) == 0x58);
}
