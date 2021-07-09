#pragma once

#include "RE/B/BSTArray.h"
#include "RE/F/FormTypes.h"
#include "RE/T/TESForm.h"

namespace RE
{
	class BGSListForm : public TESForm
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSListForm;
		inline static constexpr auto FORMTYPE = FormType::FormList;

		struct ChangeFlags
		{
			enum ChangeFlag : std::uint32_t
			{
				kAddedForm = (std::uint32_t)1 << 31
			};
		};

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		~BGSListForm() override;  // 00

		// override (TESForm)
		void ClearData() override;                         // 05
		bool Load(TESFile* a_mod) override;                // 06
		void SaveGame(BGSSaveFormBuffer* a_buf) override;  // 0E
		void LoadGame(BGSLoadFormBuffer* a_buf) override;  // 0F
		void Revert(BGSLoadFormBuffer* a_buf) override;    // 12
		void InitItemImpl() override;                      // 13

		void AddForm(TESForm* a_form);
		bool HasForm(const TESForm* a_form) const;
		[[nodiscard]] bool HasForm(FormID a_formID) const;

		// members
		BSTArray<TESForm*> forms;                 // 20 - LNAM
		BSTArray<FormID>*  scriptAddedTempForms;  // 38
		std::uint32_t      scriptAddedFormCount;  // 40
		std::uint32_t      pad44;                 // 44
	};
	static_assert(sizeof(BGSListForm) == 0x48);
}
