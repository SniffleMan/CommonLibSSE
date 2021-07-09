#pragma once

#include "RE/A/ActorValues.h"
#include "RE/B/BGSDestructibleObjectForm.h"
#include "RE/B/BGSKeywordForm.h"
#include "RE/B/BGSMessageIcon.h"
#include "RE/B/BGSPickupPutdownSounds.h"
#include "RE/F/FormTypes.h"
#include "RE/T/TESBoundObject.h"
#include "RE/T/TESDescription.h"
#include "RE/T/TESFullName.h"
#include "RE/T/TESIcon.h"
#include "RE/T/TESModelTextureSwap.h"
#include "RE/T/TESValueForm.h"
#include "RE/T/TESWeightForm.h"

namespace RE
{
	struct OBJ_BOOK  // DATA
	{
		enum class Flag
		{
			kNone = 0,
			kAdvancesActorValue = 1 << 0,
			kCantTake = 1 << 1,
			kTeachesSpell = 1 << 2,  // takes priority over skill
			kHasBeenRead = 1 << 3
		};

		enum class Type
		{
			kBookTome = 0x00,
			kNoteScroll = static_cast<std::underlying_type_t<Type>>(-1),
		};

		union Teaches
		{
			ActorValue actorValueToAdvance;
			SpellItem* spell;
		};
		static_assert(sizeof(Teaches) == 0x8);

		[[nodiscard]] Flag GetSanitizedType() const;

		// members
		stl::enumeration<Flag, std::uint8_t> flags;    // 00
		stl::enumeration<Type, std::uint8_t> type;     // 01
		std::uint16_t                        pad02;    // 02
		std::uint32_t                        pad04;    // 04
		Teaches                              teaches;  // 08
	};
	static_assert(sizeof(OBJ_BOOK) == 0x10);

	class TESObjectBOOK :
		public TESBoundObject,             // 00
		public TESFullName,                // 30
		public TESModelTextureSwap,        // 40
		public TESIcon,                    // 78
		public TESValueForm,               // 88
		public TESWeightForm,              // 98
		public TESDescription,             // A8
		public BGSDestructibleObjectForm,  // B8
		public BGSMessageIcon,             // C8
		public BGSPickupPutdownSounds,     // E0
		public BGSKeywordForm              // F8
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESObjectBOOK;
		inline static constexpr auto FORMTYPE = FormType::Book;

		struct ChangeFlags
		{
			enum ChangeFlag : std::uint32_t
			{
				kTeachesSkill = 1 << 5,
				kRead = 1 << 6
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

		~TESObjectBOOK() override;  // 00

		// override (TESBoundObject)
		void InitializeData() override;                                                                                                                                // 04
		void ClearData() override;                                                                                                                                     // 05 - { return TESForm::ClearData(); }
		bool Load(TESFile* a_mod) override;                                                                                                                            // 06
		void SaveGame(BGSSaveFormBuffer* a_buf) override;                                                                                                              // 0E
		void LoadGame(BGSLoadFormBuffer* a_buf) override;                                                                                                              // 0F
		void InitItemImpl() override;                                                                                                                                  // 13
		bool Activate(TESObjectREFR* a_targetRef, TESObjectREFR* a_activatorRef, std::uint8_t a_arg3, TESBoundObject* a_object, std::int32_t a_targetCount) override;  // 37
		bool GetActivateText(TESObjectREFR* a_activator, BSString& a_dst) override;                                                                                    // 4D

		// override (BGSKeywordForm)
		[[nodiscard]] BGSKeyword* GetDefaultKeyword() const override;  // 05

		[[nodiscard]] bool       TeachesSkill() const;
		[[nodiscard]] bool       TeachesSpell() const;
		[[nodiscard]] bool       IsRead() const;
		[[nodiscard]] bool       CanBeTaken() const;
		[[nodiscard]] bool       IsBookTome() const;
		[[nodiscard]] bool       IsNoteScroll() const;
		[[nodiscard]] ActorValue GetSkill() const;
		SpellItem* GetSpell();

		// members
		OBJ_BOOK       data;                 // 110 - DATA
		TESObjectSTAT* inventoryModel;       // 120 - INAM
		TESDescription itemCardDescription;  // 128 - CNAM
	};
	static_assert(sizeof(TESObjectBOOK) == 0x138);
}
