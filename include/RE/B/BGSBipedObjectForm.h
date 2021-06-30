#pragma once

#include "RE/B/BaseFormComponent.h"

namespace RE
{
	struct BIPED_MODEL  // BOD2
	{
	public:
		enum class BipedObjectSlot
		{
			kNone = 0,
			kHead = 1 << 0,
			kHair = 1 << 1,
			kBody = 1 << 2,
			kHands = 1 << 3,
			kForearms = 1 << 4,
			kAmulet = 1 << 5,
			kRing = 1 << 6,
			kFeet = 1 << 7,
			kCalves = 1 << 8,
			kShield = 1 << 9,
			kTail = 1 << 10,
			kLongHair = 1 << 11,
			kCirclet = 1 << 12,
			kEars = 1 << 13,
			kDecapitateHead = 1 << 20,
			kDecapitate = 1 << 21,
			kFX01 = 1 << 31
		};

		enum class ArmorType
		{
			kLightArmor,
			kHeavyArmor,
			kClothing
		};

		// members
		stl::enumeration<BipedObjectSlot, std::uint32_t> bipedObjectSlots;  // 0
		stl::enumeration<ArmorType, std::uint32_t>       armorType;         // 4
	};
	static_assert(sizeof(BIPED_MODEL) == 0x8);

	class BGSBipedObjectForm : public BaseFormComponent
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSBipedObjectForm;

		using ArmorType = BIPED_MODEL::ArmorType;
		using BipedObjectSlot = BIPED_MODEL::BipedObjectSlot;
		using FirstPersonFlag = BIPED_MODEL::BipedObjectSlot;

		~BGSBipedObjectForm() override;  // 00

		// override (BaseFormComponent)
		void InitializeDataComponent() override;                // 01
		void ClearDataComponent() override;                     // 02 - { return; }
		void CopyComponent(BaseFormComponent* a_rhs) override;  // 03

		BipedObjectSlot AddSlotToMask(BipedObjectSlot a_slot);
		[[nodiscard]] ArmorType       GetArmorType() const;
		[[nodiscard]] BipedObjectSlot GetSlotMask() const;
		[[nodiscard]] bool            HasPartOf(BipedObjectSlot a_flag) const;
		[[nodiscard]] bool            IsClothing() const;
		[[nodiscard]] bool            IsHeavyArmor() const;
		[[nodiscard]] bool            IsLightArmor() const;
		[[nodiscard]] bool            IsShield() const;
		BipedObjectSlot RemoveSlotFromMask(BipedObjectSlot a_slot);
		void            SetSlotMask(BipedObjectSlot a_mask);

		// members
		BIPED_MODEL bipedModelData;  // 08 - BOD2
	};
	static_assert(sizeof(BGSBipedObjectForm) == 0x10);
}
