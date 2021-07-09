#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/D/DialogueTypes.h"
#include "RE/F/FormTypes.h"
#include "RE/T/TESForm.h"
#include "RE/T/TESFullName.h"

namespace RE
{
	struct DIALOGUE_DATA  // DATA
	{
		enum class TopicFlag
		{
			kNone = 0,
			kDoAllBeforeRepeating = 1 << 0
		};

		enum class Subtype
		{
			kCustom = 0,
			kForceGreet = 1,
			kRumors = 2,
			kUnk3 = 3,  // custom?
			kIntimidate = 4,
			kFlatter = 5,
			kBribe = 6,
			kAskGift = 7,
			kGift = 8,
			kAskFavor = 9,
			kFavor = 10,
			kShowRelationships = 11,
			kFollow = 12,
			kReject = 13,
			kScene = 14,
			kShow = 15,
			kAgree = 16,
			kRefuse = 17,
			kExitFavorState = 18,
			kMoralRefusal = 19,
			kFlyingMountLand = 20,
			kFlyingMountCancelLand = 21,
			kFlyingMountAcceptTarget = 22,
			kFlyingMountRejectTarget = 23,
			kFlyingMountNoTarget = 24,
			kFlyingMountDestinationReached = 25,
			kAttack = 26,
			kPowerAttack = 27,
			kBash = 28,
			kHit = 29,
			kFlee = 30,
			kBleedout = 31,
			kAvoidThreat = 32,
			kDeath = 33,
			kGroupStrategy = 34,
			kBlock = 35,
			kTaunt = 36,
			kAllyKilled = 37,
			kSteal = 38,
			kYield = 39,
			kAcceptYield = 40,
			kPickpocketCombat = 41,
			kAssault = 42,
			kMurder = 43,
			kAssaultNPC = 44,
			kMurderNPC = 45,
			kPickpocketNPC = 46,
			kStealFromNPC = 47,
			kTrespassAgainstNPC = 48,
			kTrespass = 49,
			kWereTransformCrime = 50,
			kVoicePowerStartShort = 51,
			kVoicePowerStartLong = 52,
			kVoicePowerEndShort = 53,
			kVoicePowerEndLong = 54,
			kAlertIdle = 55,
			kLostIdle = 56,
			kNormalToAlert = 57,
			kAlertToCombat = 58,
			kNormalToCombat = 59,
			kAlertToNormal = 60,
			kCombatToNormal = 61,
			kCombatToLost = 62,
			kLostToNormal = 63,
			kLostToCombat = 64,
			kDetectFriendDie = 65,
			kServiceRefusal = 66,
			kRepair = 67,
			kTravel = 68,
			kTraining = 69,
			kBarterExit = 70,
			kRepairExit = 71,
			kRecharge = 72,
			kRechargeExit = 73,
			kTrainingExit = 74,
			kObserveCombat = 75,
			kNoticeCorpse = 76,
			kTimeToGo = 77,
			kGoodBye = 78,
			kHello = 79,
			kSwingMeleeWeapon = 80,
			kShootBow = 81,
			kZKeyObject = 82,
			kJump = 83,
			kKnockOverObject = 84,
			kDestroyObject = 85,
			kStandonFurniture = 86,
			kLockedObject = 87,
			kPickpocketTopic = 88,
			kPursueIdleTopic = 89,
			kSharedInfo = 90,
			kPlayerCastProjectileSpell = 91,
			kPlayerCastSelfSpell = 92,
			kPlayerShout = 93,
			kIdle = 94,
			kEnterSprintBreath = 95,
			kEnterBowZoomBreath = 96,
			kExitBowZoomBreath = 97,
			kActorCollidewithActor = 98,
			kPlayerinIronSights = 99,
			kOutofBreath = 100,
			kCombatGrunt = 101,
			kLeaveWaterBreath = 102
		};

		stl::enumeration<TopicFlag, std::uint8_t>     topicFlags;  // 0
		stl::enumeration<DIALOGUE_TYPE, std::uint8_t> type;        // 1
		stl::enumeration<Subtype, std::uint16_t>      subtype;     // 2
	};
	static_assert(sizeof(DIALOGUE_DATA) == 0x4);

	class TESTopic :
		public TESForm,     // 00
		public TESFullName  // 20
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESTopic;
		inline static constexpr auto FORMTYPE = FormType::Dialogue;

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		~TESTopic() override;  // 00

		// override (TESForm)
		bool        Load(TESFile* a_mod) override;                // 06
		void        InitItemImpl() override;                      // 13
		const char* GetFormEditorID() const override;             // 32 - { return formEditorID.c_str(); }
		bool        SetFormEditorID(const char* a_str) override;  // 33 - { bool result = formEditorID == a_str; formEditorID = a_str; return result; }
		bool        IsParentForm() override;                      // 34 - { return true; }
		bool        IsFormTypeChild(FormType a_type) override;    // 36 - { return a_type == FormType::Info }

		// override (TESFullName)
		std::uint32_t GetFullNameLength() const override;  // 04
		[[nodiscard]] const char*   GetFullName() const override;        // 05

		[[nodiscard]] float GetPriority() const;

		// members
		DIALOGUE_DATA      data;                     // 30 - DATA
		std::uint32_t      priorityAndJournalIndex;  // 34 - PNAM
		BGSDialogueBranch* ownerBranch;              // 38 - BNAM
		TESQuest*          ownerQuest;               // 40 -	QNAM
		TESTopicInfo**     topicInfos;               // 48 - infoTopics[infoCount]
		std::uint32_t      numTopicInfos;            // 50 - TIFC
		std::uint32_t      firstFileOffset;          // 54
		BSFixedString      formEditorID;             // 58
	};
	static_assert(sizeof(TESTopic) == 0x60);
}
