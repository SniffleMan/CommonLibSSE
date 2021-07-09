#pragma once

#include "RE/B/BaseFormComponent.h"
#include "RE/M/MagicSystem.h"

namespace RE
{
	class EnchantmentItem;

	class TESEnchantableForm : public BaseFormComponent
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESEnchantableForm;

		~TESEnchantableForm() override;  // 00

		// override (BaseFormComponent)
		void InitializeDataComponent() override;                // 01
		void ClearDataComponent() override;                     // 02
		void CopyComponent(BaseFormComponent* a_rhs) override;  // 03

		// add
		[[nodiscard]] virtual MagicSystem::CastingType GetCastingType() const;  // 04 - { return castingType; }

		// members
		EnchantmentItem*                                          formEnchanting;       // 08 - EITM
		stl::enumeration<MagicSystem::CastingType, std::uint16_t> castingType;          // 10
		std::uint16_t                                             amountofEnchantment;  // 12 - EAMT
		std::uint32_t                                             pad14;                // 14
	};
	static_assert(sizeof(TESEnchantableForm) == 0x18);
}
