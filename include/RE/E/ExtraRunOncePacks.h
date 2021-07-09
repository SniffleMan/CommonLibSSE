#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/B/BSTList.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	struct RunOncePackage
	{
		TESPackage*   package;  // 00
		std::int8_t   day;      // 08
		std::uint8_t  pad09;    // 09
		std::uint16_t pad0A;    // 0A
		std::uint32_t pad0C;    // 0C
	};
	static_assert(sizeof(RunOncePackage) == 0x10);

	class ExtraRunOncePacks : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraRunOncePacks;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kRunOncePacks;

		~ExtraRunOncePacks() override;  // 00

		// override (BSExtraData)
		[[nodiscard]] ExtraDataType GetType() const override;  // 01 - { return kRunOncePacks; }

		// members
		BSSimpleList<RunOncePackage*>* packages;  // 10
	};
	static_assert(sizeof(ExtraRunOncePacks) == 0x18);
}
