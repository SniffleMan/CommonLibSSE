#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/B/BSTArray.h"
#include "RE/E/ExtraDataTypes.h"
#include "RE/M/MarkerUsedData.h"

namespace RE
{
	class ExtraUsedMarkers : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraUsedMarkers;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kUsedMarkers;

		~ExtraUsedMarkers() override;  // 00

		// override (BSExtraData)
		[[nodiscard]] ExtraDataType GetType() const override;  // 01 - { return kUsedMarkers; }

		// members
		BSTArray<MarkerUsedData> usedMarkers;  // 10
	};
	static_assert(sizeof(ExtraUsedMarkers) == 0x28);
}
