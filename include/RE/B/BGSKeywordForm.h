#pragma once

#include "RE/B/BaseFormComponent.h"

namespace RE
{
	class BGSKeyword;

	class BGSKeywordForm : public BaseFormComponent
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSKeywordForm;

		~BGSKeywordForm() override;  // 00

		// override (BaseFormComponent)
		void InitializeDataComponent() override;                // 01 - { return; }
		void ClearDataComponent() override;                     // 02
		void CopyComponent(BaseFormComponent* a_rhs) override;  // 03

		// add
		virtual bool        HasKeyword(const BGSKeyword* a_keyword) const;  // 04
		[[nodiscard]] virtual BGSKeyword* GetDefaultKeyword() const;                      // 05 - { return 0; }

		[[nodiscard]] bool                       HasKeyword(FormID a_formID) const;
		[[nodiscard]] std::optional<BGSKeyword*> GetKeywordAt(std::uint32_t a_idx) const;
		[[nodiscard]] std::uint32_t              GetNumKeywords() const;

		// members
		BGSKeyword**  keywords;     // 08 - KWDA
		std::uint32_t numKeywords;  // 10 - KSIZ
		std::uint32_t pad14;        // 14
	};
	static_assert(sizeof(BGSKeywordForm) == 0x18);
}
