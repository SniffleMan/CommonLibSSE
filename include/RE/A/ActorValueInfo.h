#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/F/FormTypes.h"
#include "RE/T/TESDescription.h"
#include "RE/T/TESForm.h"
#include "RE/T/TESFullName.h"
#include "RE/T/TESIcon.h"

namespace RE
{
	class BGSSkillPerkTreeNode;

	class ActorValueInfo :
		public TESForm,         // 000
		public TESFullName,     // 020
		public TESDescription,  // 030
		public TESIcon          // 040
	{
	public:
		inline static constexpr auto RTTI = RTTI_ActorValueInfo;
		inline static constexpr auto FORMTYPE = FormType::ActorValueInfo;

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		struct Skill  // AVSK
		{
			float useMult;        // 00
			float offsetMult;     // 04
			float improveMult;    // 08
			float improveOffset;  // 0C
		};
		static_assert(sizeof(Skill) == 0x10);

		~ActorValueInfo() override;  // 00

		// override (TESForm)
		void ClearData() override;           // 05
		bool Load(TESFile* a_mod) override;  // 06
		void InitItemImpl() override;        // 13

		// override (TESIcon)
		[[nodiscard]] const char* GetDefaultPath() const override;  // 06 - { return "Textures\\"; }

		// members
		const char*           enumName;      // 050
		BSFixedString         abbreviation;  // 058 - ANAM
		std::uint32_t         unk060;        // 060
		std::uint32_t         unk064;        // 064
		std::uint64_t         unk068;        // 068
		std::uint32_t         unk070;        // 070
		std::uint32_t         unk074;        // 074
		std::uint32_t         unk078;        // 078
		std::uint32_t         unk07C;        // 07C
		std::uint32_t         unk080;        // 080
		std::uint32_t         unk084;        // 084
		std::uint32_t         unk088;        // 088
		std::uint32_t         unk08C;        // 08C
		std::uint32_t         unk090;        // 090
		std::uint32_t         unk094;        // 094
		std::uint32_t         unk098;        // 098
		std::uint32_t         unk09C;        // 09C
		std::uint32_t         unk0A0;        // 0A0
		std::uint32_t         unk0A4;        // 0A4
		std::uint32_t         unk0A8;        // 0A8
		std::uint32_t         unk0AC;        // 0AC
		std::uint64_t         unk0B0;        // 0B0
		std::uint64_t         unk0B8;        // 0B8
		std::uint64_t         unk0C0;        // 0C0
		std::uint64_t         unk0C8;        // 0C8
		std::uint64_t         unk0D0;        // 0D0
		std::uint64_t         unk0D8;        // 0D8
		std::uint64_t         unk0E0;        // 0E0
		std::uint64_t         unk0E8;        // 0E8
		std::uint64_t         unk0F0;        // 0F0
		std::uint64_t         unk0F8;        // 0F8
		std::uint64_t         unk100;        // 100
		Skill*                skill;         // 108 - AVSK
		std::uint32_t         unk110;        // 110
		std::uint32_t         unk114;        // 114
		BGSSkillPerkTreeNode* perkTree;      // 118
		std::uint32_t         unk120;        // 120
		std::uint32_t         unk124;        // 124 - CNAM
	};
	static_assert(sizeof(ActorValueInfo) == 0x128);
}
