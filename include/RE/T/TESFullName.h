#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BaseFormComponent.h"

namespace RE
{
	class TESFullName : public BaseFormComponent
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESFullName;

		~TESFullName() override;

		// override (BaseFormComponent)
		void InitializeDataComponent() override;                // 01 - { name = ""; }
		void ClearDataComponent() override;                     // 02 - { return; }
		void CopyComponent(BaseFormComponent* a_rhs) override;  // 03

		// add
		[[nodiscard]] virtual std::uint32_t GetFullNameLength() const;  // 04
		[[nodiscard]] virtual const char*   GetFullName() const;        // 05

		// members
		BSFixedString fullName;  // 08 - FULL
	};
	static_assert(sizeof(TESFullName) == 0x10);
}
