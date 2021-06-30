#pragma once

#include "RE/F/FormTypes.h"
#include "RE/T/TESBoundObject.h"
#include "RE/T/TESLeveledList.h"

namespace RE
{
	class TESLevSpell :
		public TESBoundObject,  // 00
		public TESLeveledList   // 30
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESLevSpell;
		inline static constexpr auto FORMTYPE = FormType::LeveledSpell;

		struct ChangeFlags
		{
			enum ChangeFlag : std::uint32_t
			{
				kAddedObject = (std::uint32_t)1 << 31
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

		~TESLevSpell() override;  // 00

		// override (TESBoundObject)
		bool Load(TESFile* a_mod) override;                // 06
		void SaveGame(BGSSaveFormBuffer* a_buf) override;  // 0E
		void LoadGame(BGSLoadFormBuffer* a_buf) override;  // 0F
		void Revert(BGSLoadFormBuffer* a_buf) override;    // 12
		void InitItemImpl() override;                      // 13

		// override (TESLeveledList)
		[[nodiscard]] bool GetCanContainFormsOfType(FormType a_type) const override;  // 07
	};
	static_assert(sizeof(TESLevSpell) == 0x58);
}
