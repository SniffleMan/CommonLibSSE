#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class InventoryChanges;

	class ExtraContainerChanges : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraContainerChanges;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kContainerChanges;

		ExtraContainerChanges();
		explicit ExtraContainerChanges(InventoryChanges* a_changes);
		~ExtraContainerChanges() override;  // 00

		// override (BSExtraData)
		[[nodiscard]] ExtraDataType GetType() const override;  // 01 - { return kContainerChanges; }

		// members
		InventoryChanges* changes;  // 10
	};
	static_assert(sizeof(ExtraContainerChanges) == 0x18);
}
