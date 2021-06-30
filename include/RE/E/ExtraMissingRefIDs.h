#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	struct ActivateParentID
	{
		std::uint32_t refID;          // 0
		float         activateDelay;  // 4
	};
	static_assert(sizeof(ActivateParentID) == 0x8);

	class ExtraMissingRefIDs : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraMissingRefIDs;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kMissingRefIDs;

		~ExtraMissingRefIDs() override;  // 00

		// override (BSExtraData)
		[[nodiscard]] ExtraDataType GetType() const override;  // 01 - { return kMissingRefIDs; }

		// members
		ActivateParentID* unk10;  // 10
		std::uint32_t     unk18;  // 18
		std::uint32_t     unk1C;  // 1C
		std::uint64_t     unk20;  // 20
	};
	static_assert(sizeof(ExtraMissingRefIDs) == 0x28);
}
