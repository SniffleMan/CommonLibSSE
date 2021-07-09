#pragma once

#include "RE/B/BGSHeadPart.h"
#include "RE/B/BGSOverridePackCollection.h"
#include "RE/B/BSFixedString.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTEvent.h"
#include "RE/C/Color.h"
#include "RE/F/FormTypes.h"
#include "RE/M/MemoryManager.h"
#include "RE/S/Sexes.h"
#include "RE/S/SoundLevels.h"
#include "RE/T/TESActorBase.h"
#include "RE/T/TESRaceForm.h"

namespace RE
{
	class BSFaceGenNiNode;
	class MenuOpenCloseEvent;
	class NiColorA;
	class TintMask;

	class CreatureSounds
	{
	public:
		// members
		BSTArray<void*>* unk00[8];  // 00
	};
	static_assert(sizeof(CreatureSounds) == 0x40);

	class TESNPC :
		public TESActorBase,                     // 000
		public TESRaceForm,                      // 150
		public BGSOverridePackCollection,        // 160
		public BSTEventSink<MenuOpenCloseEvent>  // 188
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESNPC;

		using HeadPartType = BGSHeadPart::HeadPartType;
		inline static constexpr auto FORMTYPE = FormType::NPC;

		struct ChangeFlags
		{
			enum ChangeFlag : std::uint32_t
			{
				kBaseData = 1 << 1,
				kAttributes = 1 << 2,
				kAIData = 1 << 3,
				kSpellList = 1 << 4,
				kFullName = 1 << 5,
				kFactions = 1 << 6,
				kNPCSkills = 1 << 9,
				kClass = 1 << 10,
				kFace = 1 << 11,
				kDefaultOutfit = 1 << 12,
				kSleepOutfit = 1 << 13,
				kGender = 1 << 24,
				kRace = 1 << 25
			};
		};

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12,
				kCompressed = 1 << 18,
				kBleedoutOverride = 1 << 29
			};
		};

		struct Skills
		{
		public:
			enum
			{
				kOneHanded = 0,
				kTwoHanded = 1,
				kMarksman = 2,
				kBlock = 3,
				kSmithing = 4,
				kHeavyArmor = 5,
				kLightArmor = 6,
				kPickpocket = 7,
				kLockpicking = 8,
				kSneak = 9,
				kAlchemy = 10,
				kSpecchcraft = 11,
				kAlteration = 12,
				kConjuration = 13,
				kDestruction = 14,
				kIllusion = 15,
				kRestoration = 16,
				kEnchanting = 17,

				kTotal
			};

			// members
			std::uint8_t  values[kTotal];        // 00
			std::uint8_t  offsets[kTotal];       // 12
			std::uint16_t health;                // 24
			std::uint16_t magicka;               // 26
			std::uint16_t stamina;               // 28
			std::uint16_t pad2A;                 // 2A
			float         farawayModelDistance;  // 2C
		};
		static_assert(sizeof(Skills) == 0x30);

		struct HeadRelatedData
		{
		public:
			HeadRelatedData();
			~HeadRelatedData() = default;

			TES_HEAP_REDEFINE_NEW();

			// members
			BGSColorForm*  hairColor;    // 00 - HCLF
			BGSTextureSet* faceDetails;  // 08 - FTST
		};
		static_assert(sizeof(HeadRelatedData) == 0x10);

		union Sounds
		{
			TESNPC*         soundCreature;
			CreatureSounds* creatureSounds;
		};
		static_assert(sizeof(Sounds) == 0x8);

		struct FaceData
		{
		public:
			struct Morphs
			{
				enum
				{
					kNose_LongShort = 0,
					kNose_UpDown = 1,
					kJaw_UpDown = 2,
					kJaw_NarrowWide = 3,
					kJaw_ForwardBack = 4,
					kCheeks_UpDown = 5,
					kCheeks_ForwardBack = 6,
					kEyes_UpDown = 7,
					kEyes_InOut = 8,
					kBrows_UpDown = 9,
					kBrows_InOut = 10,
					kBrows_ForwardBack = 11,
					kLips_UpDown = 12,
					kLips_InOut = 13,
					kChin_NarrowWide = 14,
					kChin_UpDown = 15,
					kChin_UnderbiteOverbite = 16,
					kEyes_ForwardBack = 17,
					kUnk = 18,

					kTotal = 19
				};
			};

			struct Parts
			{
				enum
				{
					kNose = 0,
					kUnknown = 1,
					kEyes = 2,
					kMouth = 3,

					kTotal = 4
				};
			};

			enum
			{
				kDefault = 0x7F7FFFFF,
				kTotalPresets = 4
			};

			// members
			float        morphs[Morphs::kTotal];  // 00 - NAM9
			std::int32_t parts[Parts::kTotal];    // 4C - NAMA
		};
		static_assert(sizeof(FaceData) == 0x5C);

		struct Layer
		{
		public:
			[[nodiscard]] float GetInterpolationValue() const;

			// members
			Color         tintColor;           // 00 - TINC
			std::uint16_t tintIndex;           // 04 - TINI
			std::uint16_t preset;              // 06 - TIAS
			std::uint16_t interpolationValue;  // 08 - TINV - CK value * 100 as an int
			std::uint16_t pad0A;               // 0A
			std::uint32_t pad0C;               // 0C
		};
		static_assert(sizeof(Layer) == 0x10);

		~TESNPC() override;  // 00

		// override (TESActorBase)
		void            InitializeData() override;                                                                                                                                // 04
		void            ClearData() override;                                                                                                                                     // 05
		bool            Load(TESFile* a_mod) override;                                                                                                                            // 06
		bool            FindInFileFast(TESFile* a_mod) override;                                                                                                                  // 0C
		void            SaveGame(BGSSaveFormBuffer* a_buf) override;                                                                                                              // 0E
		void            LoadGame(BGSLoadFormBuffer* a_buf) override;                                                                                                              // 0F
		void            Revert(BGSLoadFormBuffer* a_buf) override;                                                                                                                // 12
		void            InitItemImpl() override;                                                                                                                                  // 13
		const char*     GetTextForParsedSubTag(const BSFixedString& a_tag) const override;                                                                                        // 2E
		void            Copy(TESForm* a_srcForm) override;                                                                                                                        // 2F
		bool            Activate(TESObjectREFR* a_targetRef, TESObjectREFR* a_activatorRef, std::uint8_t a_arg3, TESBoundObject* a_object, std::int32_t a_targetCount) override;  // 37
		void            UnClone3D(TESObjectREFR* a_ref) override;                                                                                                                 // 41
		void            SetObjectVoiceType(BGSVoiceType* a_voiceType) override;                                                                                                   // 48 - { TESActorBaseData::voice = a_voiceType; }
		BGSVoiceType*   GetObjectVoiceType() const override;                                                                                                                      // 49
		NiAVObject*     Clone3D(TESObjectREFR* a_ref) override;                                                                                                                   // 4A
		bool            GetActivateText(TESObjectREFR* a_activator, BSString& a_dst) override;                                                                                    // 4C
		bool            CalculateDoFavor(Actor* a_activator, bool a_arg2, TESObjectREFR* a_toActivate, float a_arg3) override;                                                    // 4D
		TESCombatStyle* GetCombatStyle() override;                                                                                                                                // 54 - { return combatStyle; }
		void            SetCombatStyle(TESCombatStyle* a_combatStyle) override;                                                                                                   // 55 - { combatStyle = a_combatStyle; }

		// override (TESActorBaseData)
		void CopyFromTemplateForms(TESActorBase** a_templateForms) override;  // 04

		// override (ActorValueOwner)
		float GetActorValue(ActorValue a_akValue) override;                 // 01
		void  SetActorValue(ActorValue a_akValue, float a_value) override;  // 07

		// override (BSTEventSink<MenuOpenCloseEvent>)
		BSEventNotifyControl ProcessEvent(const MenuOpenCloseEvent* a_event, BSTEventSource<MenuOpenCloseEvent>* a_eventSource) override;  // 01

		void          ChangeHeadPart(BGSHeadPart* a_target);
		[[nodiscard]] BGSHeadPart** GetBaseOverlays() const;
		BGSHeadPart*  GetCurrentHeadPartByType(HeadPartType a_type);
		BGSHeadPart*  GetHeadPartByType(HeadPartType a_type);
		BGSHeadPart*  GetHeadPartOverlayByType(HeadPartType a_type);
		[[nodiscard]] float         GetHeight() const;
		[[nodiscard]] std::uint32_t GetNumBaseOverlays() const;
		TESRace*      GetRace();
		TESNPC*       GetRootFaceNPC();
		[[nodiscard]] const TESNPC* GetRootFaceNPC() const;
		[[nodiscard]] SEX           GetSex() const;
		bool          HasOverlays();
		void          SetFaceTexture(BGSTextureSet* a_textureSet);
		void          SetHairColor(BGSColorForm* a_hairColor);
		void          SetSkinFromTint(NiColorA* a_result, TintMask* a_tintMask, bool a_fromTint);
		void          UpdateNeck(BSFaceGenNiNode* a_faceNode);

		// members
		Skills                                      playerSkills;     // 190 - DNAM
		TESClass*                                   npcClass;         // 1C0 - CNAM
		HeadRelatedData*                            headRelatedData;  // 1C8
		BGSListForm*                                giftFilter;       // 1D0 - GNAM
		TESCombatStyle*                             combatStyle;      // 1D8 - ZNAM
		std::uint32_t                               fileOffset;       // 1E0
		std::uint32_t                               pad1E4;           // 1E4
		TESRace*                                    originalRace;     // 1E8
		TESNPC*                                     faceNPC;          // 1F0
		float                                       height;           // 1F8 - NAM6
		float                                       weight;           // 1FC - NAM7
		Sounds                                      sounds;           // 200 - CSCR
		BSFixedString                               shortName;        // 208 - SHRT
		TESObjectARMO*                              farSkin;          // 210 - ANAM
		BGSOutfit*                                  defaultOutfit;    // 218 - DOFT
		BGSOutfit*                                  sleepOutfit;      // 220 - SOFT
		BGSListForm*                                defaultPackList;  // 228 - DPLT
		TESFaction*                                 crimeFaction;     // 230 - CRIF
		BGSHeadPart**                               headParts;        // 238 - PNAM
		std::int8_t                                 numHeadParts;     // 240
		std::uint8_t                                unk241;           // 241
		std::uint8_t                                unk242;           // 242
		std::uint8_t                                unk243;           // 243
		std::uint8_t                                unk244;           // 244
		stl::enumeration<SOUND_LEVEL, std::uint8_t> soundLevel;       // 245 - NAM8
		Color                                       bodyTintColor;    // 246 - QNAM
		std::uint16_t                               pad24A;           // 24A
		std::uint32_t                               pad24C;           // 24C
		BSTArray<BGSRelationship*>*                 relationships;    // 250
		FaceData*                                   faceData;         // 258
		BSTArray<Layer*>*                           tintLayers;       // 260
	};
	static_assert(sizeof(TESNPC) == 0x268);
}
