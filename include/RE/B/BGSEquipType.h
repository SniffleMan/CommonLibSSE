#pragma once

#include "RE/B/BaseFormComponent.h"
#include "RE/F/FormTypes.h"

namespace RE
{
	class BGSEquipType : public BaseFormComponent  // EQUP
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSEquipType;

		enum class EQUIPPED_ITEM_TYPE
		{
			kSpell = 24,
			kShield = 25,
			kTorch = 26,

			kTotal
		};

		~BGSEquipType() override;  // 00

		// override (BaseFormComponent)
		void InitializeDataComponent() override;                // 01 - { equipSlot = 0; }
		void ClearDataComponent() override;                     // 02 - { return; }
		void CopyComponent(BaseFormComponent* a_rhs) override;  // 03

		// add
		[[nodiscard]] virtual BGSEquipSlot* GetEquipSlot() const;                // 04 - { return equipSlot; }
		virtual void          SetEquipSlot(BGSEquipSlot* a_slot);  // 05 - { equipSlot = a_slot; }

		// members
		BGSEquipSlot* equipSlot;  // 08 - ETYP
	};
	static_assert(sizeof(BGSEquipType) == 0x10);
}
