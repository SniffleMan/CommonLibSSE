#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	struct BGSDecalGroup;

	class ExtraDecalGroup : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraDecalGroup;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kDecalGroup;

		~ExtraDecalGroup() override;  // 00

		// override (BSExtraData)
		[[nodiscard]] ExtraDataType GetType() const override;  // 01 - { return kDecalGroup; }

		// members
		BGSDecalGroup* decalGroup;  // 10
	};
	static_assert(sizeof(ExtraDecalGroup) == 0x18);
}
