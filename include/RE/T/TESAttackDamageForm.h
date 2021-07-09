#pragma once

#include "RE/B/BaseFormComponent.h"

namespace RE
{
	class TESAttackDamageForm : public BaseFormComponent
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESAttackDamageForm;

		~TESAttackDamageForm() override;  // 00

		// override (BaseFormComponent)
		void InitializeDataComponent() override;                // 01 - { attackDamage = 0; }
		void ClearDataComponent() override;                     // 02 - { return; }
		void CopyComponent(BaseFormComponent* a_rhs) override;  // 03

		// add
		[[nodiscard]] virtual std::uint16_t GetAttackDamage() const;  // 04 - { return attackDamage; }

		// members
		std::uint16_t attackDamage;  // 08
		std::uint16_t pad0A;         // 0A
		std::uint32_t pad0C;         // 0C
	};
	static_assert(sizeof(TESAttackDamageForm) == 0x10);
}
