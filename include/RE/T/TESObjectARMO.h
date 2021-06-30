#pragma once

#include "RE/B/BGSBipedObjectForm.h"
#include "RE/B/BGSBlockBashData.h"
#include "RE/B/BGSDestructibleObjectForm.h"
#include "RE/B/BGSEquipType.h"
#include "RE/B/BGSKeywordForm.h"
#include "RE/B/BGSPickupPutdownSounds.h"
#include "RE/B/BSTArray.h"
#include "RE/F/FormTypes.h"
#include "RE/T/TESBipedModelForm.h"
#include "RE/T/TESBoundObject.h"
#include "RE/T/TESDescription.h"
#include "RE/T/TESEnchantableForm.h"
#include "RE/T/TESFullName.h"
#include "RE/T/TESRaceForm.h"
#include "RE/T/TESValueForm.h"
#include "RE/T/TESWeightForm.h"

namespace RE
{
	class TESObjectARMO :
		public TESBoundObject,             // 000
		public TESFullName,                // 030
		public TESRaceForm,                // 040
		public TESEnchantableForm,         // 050
		public TESValueForm,               // 068
		public TESWeightForm,              // 078
		public BGSDestructibleObjectForm,  // 088
		public BGSPickupPutdownSounds,     // 098
		public TESBipedModelForm,          // 0B0
		public BGSEquipType,               // 1A0
		public BGSBipedObjectForm,         // 1B0
		public BGSBlockBashData,           // 1C0
		public BGSKeywordForm,             // 1D8
		public TESDescription              // 1F0
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESObjectARMO;
		inline static constexpr auto FORMTYPE = FormType::Armor;

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kNonPlayable = 1 << 2,
				kDeleted = 1 << 5,
				kShield = 1 << 6,
				kIgnored = 1 << 12
			};
		};

		// override (TESBoundObject)
		void     InitializeData() override;                    // 04
		bool     Load(TESFile* a_mod) override;                // 06
		void     SaveGame(BGSSaveFormBuffer* a_buf) override;  // 0E
		void     LoadGame(BGSLoadFormBuffer* a_buf) override;  // 0F
		void     InitItemImpl() override;                      // 13
		TESFile* GetDescriptionOwnerFile() const override;     // 14 - { return templateArmor ? templateArmor->GetFile(-1) : GetFile(-1); }
		void     Copy(TESForm* a_srcForm) override;            // 2F

		// override (BGSKeywordForm)
		[[nodiscard]] BGSKeyword* GetDefaultKeyword() const override;  // 05

		float GetArmorRating();

		// members
		std::uint32_t            armorRating;    // 200 - DNAM - CK value * 100 as a std::uint32_t
		std::uint32_t            pad204;         // 204
		BSTArray<TESObjectARMA*> armorAddons;    // 208
		TESObjectARMO*           templateArmor;  // 220 - TNAM
	};
	static_assert(sizeof(TESObjectARMO) == 0x228);
}
