#pragma once

#include "RE/A/ActorValues.h"
#include "RE/B/BGSAttackDataForm.h"
#include "RE/B/BGSBehaviorGraphModel.h"
#include "RE/B/BGSBipedObjectForm.h"
#include "RE/B/BGSKeywordForm.h"
#include "RE/B/BGSSkinForm.h"
#include "RE/B/BGSTextureModel.h"
#include "RE/B/BSFixedString.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BipedObjects.h"
#include "RE/F/FormTypes.h"
#include "RE/N/NiPoint3.h"
#include "RE/S/Sexes.h"
#include "RE/T/TESDescription.h"
#include "RE/T/TESForm.h"
#include "RE/T/TESFullName.h"
#include "RE/T/TESModel.h"
#include "RE/T/TESSpellList.h"
#include "RE/T/TESTexture.h"

namespace RE
{
	class AttackAnimationArrayMap;

	namespace BSResource
	{
		struct ID;
	}

	enum class RACE_SIZE
	{
		kSmall = 0,
		kMedium = 1,
		kLarge = 2,
		kExtraLarge = 3
	};

	struct RACE_DATA
	{
	public:
		enum
		{
			kNumSkillBoosts = 7
		};

		enum class Flag
		{
			kNone = 0,
			kPlayable = 1 << 0,
			kFaceGenHead = 1 << 1,
			kChild = 1 << 2,
			kTiltFrontBack = 1 << 3,
			kTiltLeftRight = 1 << 4,
			kNoShadow = 1 << 5,
			kSwims = 1 << 6,
			kFlies = 1 << 7,
			kWalks = 1 << 8,
			kImmobile = 1 << 9,
			kNotPushable = 1 << 10,
			kNoCombatInWater = 1 << 11,
			kNoRotatingToHeadTrack = 1 << 12,
			kDontShowBloodSpray = 1 << 13,
			kDontShowBloodDecal = 1 << 14,
			kUseHeadTrackAnims = 1 << 15,
			kSpellsAlignWithMagicNode = 1 << 16,
			kUseWorldRaycastsForFootIK = 1 << 17,
			kAllowRagdollCollision = 1 << 18,
			kRegenHPInCombat = 1 << 19,
			kCantOpenDoors = 1 << 20,
			kAllowPCDialogue = 1 << 21,
			kNoKnockdowns = 1 << 22,
			kAllowPickpocket = 1 << 23,
			kAlwaysUseProxyController = 1 << 24,
			kDontShowWeaponBlood = 1 << 25,
			kOverlayHeadPartList = 1 << 26,
			kOverrideHeadPartList = 1 << 27,
			kCanPickupItems = 1 << 28,
			kAllowMultipleMembraneShaders = 1 << 29,
			kCanDualWield = 1 << 30,
			kAvoidsRoads = 1 << 31,
		};

		enum class Flag2
		{
			kNone = 0,
			kUseAdvancedAvoidance = 1 << 0,
			kNonHostile = 1 << 1,
			kAllowMountedCombat = 1 << 4
		};

		struct SkillBoost
		{
		public:
			// members
			stl::enumeration<ActorValue, std::uint8_t> skill;  // 0
			std::uint8_t                               bonus;  // 1
		};
		static_assert(sizeof(SkillBoost) == 0x2);

		// members
		SkillBoost                                    skillBoosts[kNumSkillBoosts];  // 00
		std::uint16_t                                 pad0E;                         // 0E
		float                                         height[SEXES::kTotal];         // 10
		float                                         weight[SEXES::kTotal];         // 18
		stl::enumeration<Flag, std::uint32_t>         flags;                         // 20
		float                                         startingHealth;                // 24
		float                                         startingMagicka;               // 28
		float                                         startingStamina;               // 2C
		float                                         baseCarryWeight;               // 30
		float                                         baseMass;                      // 34
		float                                         accelerate;                    // 38
		float                                         decelerate;                    // 3C
		stl::enumeration<RACE_SIZE, std::uint32_t>    raceSize;                      // 40
		stl::enumeration<BIPED_OBJECT, std::uint32_t> headObject;                    // 44
		stl::enumeration<BIPED_OBJECT, std::uint32_t> hairObject;                    // 48
		float                                         injuredHealthPercent;          // 4C
		stl::enumeration<BIPED_OBJECT, std::uint32_t> shieldObject;                  // 50
		float                                         healthRegen;                   // 54
		float                                         magickaRegen;                  // 58
		float                                         staminaRegen;                  // 5C
		float                                         unarmedDamage;                 // 60
		float                                         unarmedReach;                  // 64
		stl::enumeration<BIPED_OBJECT, std::uint32_t> bodyObject;                    // 68
		float                                         aimAngleTolerance;             // 6C
		float                                         flightRadius;                  // 70
		float                                         angleAccelerate;               // 74
		float                                         angleTolerance;                // 78
		stl::enumeration<Flag2, std::uint32_t>        flags2;                        // 7C
		NiPoint3                                      mountOffset;                   // 80
		NiPoint3                                      dismountOffset;                // 8C
		NiPoint3                                      mountCameraOffset;             // 98
	};
	static_assert(sizeof(RACE_DATA) == 0xA4);

	class TESRace :
		public TESForm,             // 000
		public TESFullName,         // 020
		public TESDescription,      // 030
		public TESSpellList,        // 040
		public BGSSkinForm,         // 050
		public BGSBipedObjectForm,  // 060
		public BGSKeywordForm,      // 070
		public BGSAttackDataForm    // 088
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESRace;
		inline static constexpr auto FORMTYPE = FormType::Race;

		enum class EquipmentFlag
		{
			kNone = 0,
			kHandToHandMelee = 1 << 0,
			kOneHandSword = 1 << 1,
			kOneHandDagger = 1 << 2,
			kOneHandAxe = 1 << 3,
			kOneHandMace = 1 << 4,
			kTwoHandSword = 1 << 5,
			kTwoHandAxe = 1 << 6,
			kBow = 1 << 7,
			kStaff = 1 << 8,
			kSpell = 1 << 9,
			kShield = 1 << 10,
			kTorch = 1 << 11,
			kCrossbow = 1 << 12
		};

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12,
				kCritter = 1 << 19  // ?
			};
		};

		struct MovementTypes
		{
			enum
			{
				kWalk = 0,
				kRun,
				kSwim,
				kFly,
				kSneak,
				kSprint,
				kTotal
			};
		};

		struct FaceRelatedData
		{
			enum
			{
				kNose = 0,
				kBrows,
				kEyes,
				kLips,

				kNumVariants
			};

			struct Morph
			{
			public:
				// members
				std::uint32_t morphFlags;  // 00
				std::uint32_t unk04;       // 04
				std::uint32_t unk08;       // 08
				std::uint32_t unk0C;       // 0C
				std::uint32_t unk10;       // 10
				std::uint32_t unk14;       // 14
				std::uint32_t unk18;       // 18
				std::uint32_t unk1C;       // 1C
			};
			static_assert(sizeof(Morph) == 0x20);

			struct TintAsset
			{
			public:
				struct TintLayer
				{
				public:
					enum class SkinTone
					{
						kNone = 0,
						kLipColor = 1,
						kCheekColor = 2,
						kEyeliner = 3,
						kEyeSocketUpper = 4,
						kEyeSocketLower = 5,
						kSkinTone = 6,
						kPaint = 7,
						kLaughLines = 8,
						kCheekColorLower = 9,
						kNose = 10,
						kChin = 11,
						kNeck = 12,
						kForehead = 13,
						kDirt = 14,
					};

					// members
					std::uint16_t                            index;          // 00 - TINI
					stl::enumeration<SkinTone, std::uint8_t> skinTone;       // 02 - TINP
					std::uint8_t                             pad03;          // 03
					std::uint32_t                            pad04;          // 04
					TESTexture                               file;           // 08 - TINT
					BGSColorForm*                            presetDefault;  // 18 - TIND
				};
				static_assert(sizeof(TintLayer) == 0x20);

				struct Presets
				{
				public:
					// members
					BSTArray<BGSColorForm*> colors;         // 00 - TINC
					BSTArray<float>         defaultValues;  // 18 - TINV
					BSTArray<std::uint16_t> indices;        // 30 - TIRS
				};
				static_assert(sizeof(Presets) == 0x48);

				// members
				TintLayer texture;  // 00
				Presets   presets;  // 20
			};
			static_assert(sizeof(TintAsset) == 0x68);

			// members
			Morph                     availableMorphs[kNumVariants];  // 00
			std::uint32_t             numFlagsSet[kNumVariants];      // 80
			BSTArray<TintAsset*>*     tintMasks;                      // 90
			BSTArray<BGSTextureSet*>* faceDetailsTextureSets;         // 98 - FTSM / FTSF
			BGSTextureSet*            defaultFaceDetailsTextureSet;   // A0 - DFTM / DFTF
			BSTArray<TESNPC*>*        presetNPCs;                     // A8 - RPRM / RPRF
			BSTArray<BGSColorForm*>*  availableHairColors;            // B0 - AHCM / AHCF
			BGSColorForm*             defaultHairColor;               // B8
			BSTArray<BGSHeadPart*>*   headParts;                      // C0 - HEAD
		};
		static_assert(sizeof(FaceRelatedData) == 0xC8);

		struct UnkData
		{
		public:
			// members
			BSResource::ID** unkHashes;      // 00
			std::uint32_t    numUnkHashes1;  // 08
			std::uint32_t    pad0C;          // 0C
			std::uint32_t    numUnkHashes2;  // 10
			std::uint32_t    pad14;          // 14
		};
		static_assert(sizeof(UnkData) == 0x18);

		~TESRace() override;  // 00

		// override (TESForm)
		void        InitializeData() override;                    // 04
		void        ClearData() override;                         // 05
		bool        Load(TESFile* a_mod) override;                // 06
		void        InitItemImpl() override;                      // 13
		bool        GetPlayable() const override;                 // 19
		const char* GetFormEditorID() const override;             // 32 - { return formEditorID.c_str(); }
		bool        SetFormEditorID(const char* a_str) override;  // 33 - { formEditorID = a_str; }

		[[nodiscard]] bool AllowsPCDialogue() const;
		[[nodiscard]] bool AllowsPickpocket() const;

		// members
		TESModel                                       skeletonModels[SEXES::kTotal];                  // 098 - ANAM
		RACE_DATA                                      data;                                           // 0E8
		float                                          clampFaceGeoValue;                              // 18C - PNAM
		float                                          clampFaceGeoValue2;                             // 18C - UNAM
		std::uint32_t                                  pad194;                                         // 194
		BGSTextureModel                                bodyTextureModels[SEXES::kTotal];               // 198
		BGSBehaviorGraphModel                          behaviorGraphs[SEXES::kTotal];                  // 1E8
		BSFixedString                                  rootBehaviorGraphNames[SEXES::kTotal];          // 238
		BSFixedString                                  behaviorGraphProjectNames[SEXES::kTotal];       // 248
		BGSVoiceType*                                  defaultVoiceTypes[SEXES::kTotal];               // 258 - VTCK
		BGSBodyPartData*                               bodyPartData;                                   // 268 - GNAM
		TESObjectARMO*                                 decapitateArmors[SEXES::kTotal];                // 270 - DNAM
		UnkData                                        unk280;                                         // 280
		UnkData                                        unk298;                                         // 298
		std::uint64_t                                  unk2B0;                                         // 2B0
		std::uint64_t                                  unk2B8;                                         // 2B8
		std::uint64_t                                  unk2C0;                                         // 2C0
		std::uint64_t                                  unk2C8;                                         // 2C8
		AttackAnimationArrayMap*                       attackAnimationArrayMap[SEXES::kTotal];         // 2D0
		BSFixedString                                  formEditorID;                                   // 2E0 - EDID
		BGSMaterialType*                               bloodImpactMaterial;                            // 2E8 - NAM4
		BGSImpactDataSet*                              impactDataSet;                                  // 2F0 - NAM5
		BGSArtObject*                                  dismemberBlood;                                 // 2F8 - NAM7
		BGSSoundDescriptorForm*                        corpseOpenSound;                                // 300 - ONAM
		BGSSoundDescriptorForm*                        corpseCloseSound;                               // 308 - LNAM
		BSFixedString                                  bipedObjectNameA[BIPED_OBJECTS::kEditorTotal];  // 310 - NAME
		BSTArray<BGSEquipSlot*>                        equipSlots;                                     // 410 - QNAM
		stl::enumeration<EquipmentFlag, std::uint32_t> validEquipTypes;                                // 428 - VNAM - bits 13+ are always set
		std::uint32_t                                  unk42C;                                         // 42C - TESModel::unk24
		BGSEquipSlot*                                  unarmedEquipSlot;                               // 430 - UNES
		TESRace*                                       morphRace;                                      // 438 - NAM8
		TESRace*                                       armorParentRace;                                // 440 - RNAM
		UnkData                                        unk448;                                         // 448
		BSTArray<BSFixedString>                        phonemeTargets;                                 // 460 - PHTN
		BGSMovementType*                               baseMoveTypes[MovementTypes::kTotal];           // 478 - WKMV / RNMV / WMMV / FLMV / SNMV / SPMV
		FaceRelatedData*                               faceRelatedData[SEXES::kTotal];                 // 4A8
	};
	static_assert(sizeof(TESRace) == 0x4B8);
}
