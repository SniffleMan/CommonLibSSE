#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class ExtraDistantData : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraDistantData;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kDistantData;

		~ExtraDistantData() override;  // 00

		// override (BSExtraData)
		[[nodiscard]] ExtraDataType GetType() const override;  // 01 - { return kDistantData; }

		// members
		NiPoint3      landNormal;  // 10
		std::uint32_t pad1C;       // 1C
	};
	static_assert(sizeof(ExtraDistantData) == 0x20);
}
