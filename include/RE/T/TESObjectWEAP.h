#pragma once

#include "RE/A/ActorValues.h"
#include "RE/B/BGSBlockBashData.h"
#include "RE/B/BGSDestructibleObjectForm.h"
#include "RE/B/BGSEquipType.h"
#include "RE/B/BGSKeywordForm.h"
#include "RE/B/BGSMessageIcon.h"
#include "RE/B/BGSPickupPutdownSounds.h"
#include "RE/B/BGSPreloadable.h"
#include "RE/F/FormTypes.h"
#include "RE/S/SoundLevels.h"
#include "RE/T/TESAttackDamageForm.h"
#include "RE/T/TESBoundObject.h"
#include "RE/T/TESDescription.h"
#include "RE/T/TESEnchantableForm.h"
#include "RE/T/TESFullName.h"
#include "RE/T/TESIcon.h"
#include "RE/T/TESModel.h"
#include "RE/T/TESModelTextureSwap.h"
#include "RE/T/TESValueForm.h"
#include "RE/T/TESWeightForm.h"

namespace RE
{
	enum class WEAPONHITBEHAVIOR
	{
		kNormal = 0,
		kDismemberOnly = 1,
		kExplodeOnly = 2,
		kNoDismemberOrExplode = 3
	};

	enum class WEAPON_RUMBLE_PATTERN
	{
		kConstant = 0,
		kPeriodicSquare = 1,
		kPeriodicTriangle = 2,
		kPeriodicSawtooth = 3
	};

	enum class WEAPON_TYPE
	{
		kHandToHandMelee = 0,
		kOneHandSword = 1,
		kOneHandDagger = 2,
		kOneHandAxe = 3,
		kOneHandMace = 4,
		kTwoHandSword = 5,
		kTwoHandAxe = 6,
		kBow = 7,
		kStaff = 8,
		kCrossbow = 9
	};

	class TESObjectWEAP :
		public TESBoundObject,             // 000
		public TESFullName,                // 030
		public TESModelTextureSwap,        // 040
		public TESIcon,                    // 078
		public TESEnchantableForm,         // 088
		public TESValueForm,               // 0A0
		public TESWeightForm,              // 0B0
		public TESAttackDamageForm,        // 0C0
		public BGSDestructibleObjectForm,  // 0D0
		public BGSEquipType,               // 0E0
		public BGSPreloadable,             // 0F0
		public BGSMessageIcon,             // 0F8
		public BGSPickupPutdownSounds,     // 110
		public BGSBlockBashData,           // 128
		public BGSKeywordForm,             // 140
		public TESDescription              // 158
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESObjectWEAP;
		inline static constexpr auto FORMTYPE = FormType::Weapon;

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kNonPlayable = 1 << 2,
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		struct RangedData
		{
		public:
			// members
			float                                                  sightFOV;                        // 00
			float                                                  unk04;                           // 04
			float                                                  firingRumbleLeftMotorStrength;   // 08
			float                                                  firingRumbleRightMotorStrength;  // 0C
			float                                                  firingRumbleDuration;            // 10
			stl::enumeration<WEAPON_RUMBLE_PATTERN, std::uint32_t> rumblePattern;                   // 14
			std::int8_t                                            numProjectiles;                  // 18
			std::uint8_t                                           pad19;                           // 19
			std::uint16_t                                          pad1A;                           // 1A
		};
		static_assert(sizeof(RangedData) == 0x1C);

		struct Data  // DNAM
		{
		public:
			enum class Flag2
			{
				kNone = 0,
				kPlayerOnly = 1 << 0,
				kNPCsUseAmmo = 1 << 1,
				kNoJamAfterReload = 1 << 2,  // unused
				kMinorCrime = 1 << 4,
				kRangeFixed = 1 << 5,
				kNotUsedInNormalCombat = 1 << 6,
				kDontUse3rdPersonISAnim = 1 << 8,  // unused
				kBurstShot = 1 << 9,
				kRumbleAlternate = 1 << 10,
				kLongBursts = 1 << 11,
				kNonHostile = 1 << 12,
				kBoundWeapon = 1 << 13
			};

			enum class AttackAnimation
			{
				kAttackLeft = 26,
				kAttackRight = 32,
				kAttack3 = 38,
				kAttack4 = 44,
				kAttack5 = 50,
				kAttack7 = 62,
				kAttack8 = 68,
				kAttackLoop = 74,
				kAttackSpin = 80,
				kAttackSpin2 = 86,
				kPlaceMine = 97,
				kPlaceMine2 = 103,
				kAttackThrow = 109,
				kAttackThrow2 = 115,
				kAttackThrow3 = 121,
				kAttackThrow4 = 127,
				kAttackThrow5 = 133,
				kDefault = 255
			};

			enum class Flag
			{
				kNone = 0,
				kIgnoresNormalWeaponResistance = 1 << 0,
				kAutomatic = 1 << 1,  // unused
				kHasScope = 1 << 2,   // unused
				kCantDrop = 1 << 3,
				kHideBackpack = 1 << 4,              // unused
				kEmbeddedWeapon = 1 << 5,            // unused
				kDontUseFirstPersonISAnim = 1 << 6,  // unused
				kNonPlayable = 1 << 7
			};

			// members
			RangedData*                                        rangedData;           // 00
			float                                              speed;                // 08
			float                                              reach;                // 0C
			float                                              minRange;             // 10
			float                                              maxRange;             // 14
			float                                              animationAttackMult;  // 18
			float                                              unk1C;                // 1C
			float                                              staggerValue;         // 20
			stl::enumeration<WEAPONHITBEHAVIOR, std::uint32_t> hitBehavior;          // 24
			stl::enumeration<ActorValue, std::uint32_t>        skill;                // 28
			stl::enumeration<ActorValue, std::uint32_t>        resistance;           // 2C
			stl::enumeration<Flag2, std::uint16_t>             flags2;               // 30
			std::uint8_t                                       baseVATSToHitChance;  // 32
			stl::enumeration<AttackAnimation, std::uint8_t>    attackAnimation;      // 33
			stl::enumeration<ActorValue, std::uint8_t>         embeddedWeaponAV;     // 34 - unused
			stl::enumeration<WEAPON_TYPE, std::uint8_t>        animationType;        // 35
			stl::enumeration<Flag, std::uint8_t>               flags;                // 36
			std::uint8_t                                       unk37;                // 37
		};
		static_assert(sizeof(Data) == 0x38);

		struct CriticalData  // CRDT
		{
		public:
			enum Flag
			{
				kNone = 0,
				kOnDeath = 1 << 0
			};

			// members
			float                                prcntMult;  // 00
			std::uint32_t                        pad04;      // 04
			SpellItem*                           effect;     // 08
			std::uint16_t                        damage;     // 10
			stl::enumeration<Flag, std::uint8_t> flags;      // 12
			std::uint8_t                         pad13;      // 13
			std::uint32_t                        pad14;      // 14
		};
		static_assert(sizeof(CriticalData) == 0x18);

		struct Unk1B8
		{
		public:
			// members
			TESModel         unk00;  // 00
			TESEffectShader* unk28;  // 28
		};
		static_assert(sizeof(Unk1B8) == 0x30);

		~TESObjectWEAP() override;  // 00

		// override (TESBoundObject)
		void        InitializeData() override;                    // 04
		void        ClearData() override;                         // 05
		bool        Load(TESFile* a_mod) override;                // 06
		void        SaveGame(BGSSaveFormBuffer* a_buf) override;  // 0E
		void        LoadGame(BGSLoadFormBuffer* a_buf) override;  // 0F
		void        InitItemImpl() override;                      // 13
		TESFile*    GetDescriptionOwnerFile() const override;     // 14
		bool        GetPlayable() const override;                 // 19 - { return ~((data.flags >> 7) & 1); }
		const char* GetObjectTypeName() const override;           // 39 - { return g_animationStrings[data.animationType]; }

		// override (BGSKeywordForm)
		[[nodiscard]] BGSKeyword* GetDefaultKeyword() const override;  // 05

		[[nodiscard]] float         GetSpeed() const;
		[[nodiscard]] float         GetReach() const;
		[[nodiscard]] float         GetStagger() const;
		[[nodiscard]] float         GetMinRange() const;
		[[nodiscard]] float         GetMaxRange() const;
		[[nodiscard]] std::uint16_t GetCritDamage() const;
		void          GetNodeName(char* a_dstBuff) const;
		[[nodiscard]] WEAPON_TYPE   GetWeaponType() const;
		[[nodiscard]] bool          IsBound() const;
		[[nodiscard]] bool          IsMelee() const;
		[[nodiscard]] bool          IsRanged() const;
		[[nodiscard]] bool          IsHandToHandMelee() const;
		[[nodiscard]] bool          IsOneHandedSword() const;
		[[nodiscard]] bool          IsOneHandedDagger() const;
		[[nodiscard]] bool          IsOneHandedAxe() const;
		[[nodiscard]] bool          IsOneHandedMace() const;
		[[nodiscard]] bool          IsTwoHandedSword() const;
		[[nodiscard]] bool          IsTwoHandedAxe() const;
		[[nodiscard]] bool          IsBow() const;
		[[nodiscard]] bool          IsStaff() const;
		[[nodiscard]] bool          IsCrossbow() const;

		// members
		Data                                         weaponData;              // 168 - DNAM
		CriticalData                                 criticalData;            // 1A0 - CRDT
		Unk1B8*                                      unk1B8;                  // 1B8
		BGSSoundDescriptorForm*                      attackSound;             // 1C0 - SNAM
		BGSSoundDescriptorForm*                      attackSound2D;           // 1C8 - XNAM
		BGSSoundDescriptorForm*                      attackLoopSound;         // 1D0 - NAM7
		BGSSoundDescriptorForm*                      attackFailSound;         // 1D8 - TNAM
		BGSSoundDescriptorForm*                      idleSound;               // 1E0 - UNAM
		BGSSoundDescriptorForm*                      equipSound;              // 1E8 - NAM9
		BGSSoundDescriptorForm*                      unequipSound;            // 1F0 - NAM8
		BGSImpactDataSet*                            impactDataSet;           // 1F8
		TESObjectSTAT*                               firstPersonModelObject;  // 200 - WNAM
		TESObjectWEAP*                               templateWeapon;          // 208 - CNAM
		BSFixedString                                embeddedNode;            // 210
		stl::enumeration<SOUND_LEVEL, std::uint32_t> soundLevel;              // 218 - VNAM
		std::uint32_t                                pad21C;                  // 21C
	};
	static_assert(sizeof(TESObjectWEAP) == 0x220);
}
