#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class ActorPackageData;

	class ExtraPackageData : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraPackageData;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kPackageData;

		~ExtraPackageData() override;  // 00

		// override (BSExtraData)
		[[nodiscard]] ExtraDataType GetType() const override;  // 01 - { return kPackageData; }

		// members
		ActorPackageData* actorPackageData;  // 10
	};
	static_assert(sizeof(ExtraPackageData) == 0x18);
}
