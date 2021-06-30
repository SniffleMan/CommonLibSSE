#pragma once

#include "RE/B/BSPointerHandle.h"
#include "RE/F/FormTypes.h"
#include "RE/T/TESCondition.h"
#include "RE/T/TESForm.h"

namespace RE
{
	class BGSIdleCollection;
	class PackageLocation;
	class TESPackageData;

	enum class PACKAGE_OBJECT_TYPE
	{
		kNone = 0,
		kACTI = 1,
		kARMO = 2,
		kBOOK = 3,
		kCONT = 4,
		kDOOR = 5,
		kINGR = 6,
		kLIGH = 7,
		kMISC = 8,
		kFLOR = 9,
		kFURN = 10,
		kWEAP = 11,
		kAMMO = 12,
		kKEYM = 13,
		kALCH = 14,
		kFOOD = 15
	};

	enum class PACKAGE_PROCEDURE_TYPE
	{
		kNone = static_cast<std::underlying_type_t<PACKAGE_PROCEDURE_TYPE>>(-1),
		kFind = 0,
		kFollow = 1,
		kEscort = 2,
		kEat = 3,
		kSleep = 4,
		kWander = 5,
		kTravel = 6,
		kAccompany = 7,
		kUseItemAt = 8,
		kAmbush = 9,
		kFleeNotCombat = 10,
		kCastMagic = 11,
		kSandbox = 12,
		kPatrol = 13,
		kGuard = 14,
		kDialogue = 15,
		kUseWeapon = 16,
		kFind2 = 17,
		kPackage = 18,
		kPackageTemplate = 19,
		kActivate = 20,
		kAlarm = 21,
		kFlee = 22,
		kTrespass = 23,
		kSpectator = 24,
		kReactToDead = 25,
		kGetUpFromChairBed = 26,
		kDoNothing = 27,
		kInGameDialogue = 28,
		kSurface = 29,
		kSearchForAttacker = 30,
		kAvoidPlayer = 31,
		kReactToDestroyedObject = 32,
		kReactToGrenadeOrMine = 33,
		kStealWarning = 34,
		kPickPocketWarning = 35,
		kMovementBlocked = 36,
		kVampireFeed = 37,
		kCannibal = 38
	};

	enum class PACK_EVENT_ACTION_TYPE
	{
		kBegin = 0,
		kEnd,
		kChange,
		kPatrol
	};

	enum class PACK_INTERRUPT_TARGET
	{
		kNone = static_cast<std::underlying_type_t<PACK_INTERRUPT_TARGET>>(-1),
		kSpectator = 0,
		kObserveDead = 0x1,
		kGuardWarn = 0x2,
		kCombat = 0x3
	};

	struct PACKAGE_DATA  // PKDT
	{
	public:
		enum class GeneralFlag
		{
			kNone = 0,
			kOffersServices = 1 << 0,
			kMustComplete = 1 << 2,
			kMaintainSpeedAtGoal = 1 << 3,
			kUnlocksDoorsAtPackageStart = 1 << 6,
			kUnlocksDoorsAtPackageEnd = 1 << 7,
			kContinueIfPCNear = 1 << 9,
			kOncePerDay = 1 << 10,
			kPreferredSpeed = 1 << 13,
			kAlwaysSneak = 1 << 17,
			kAllowSwimming = 1 << 18,
			kIgnoreCombat = 1 << 20,
			kWeaponsUnequipped = 1 << 21,
			kWeaponDrawn = 1 << 23,
			kNoCombatAlert = 1 << 27,
			kWearSleepOutfit = 1 << 29
		};

		enum class PreferredSpeed
		{
			kWalk = 0,
			kJog = 1,
			kRun = 2,
			kFastWalk = 3
		};

		enum class InterruptFlag
		{
			kNone = 0,
			kHellosToPlayer = 1 << 0,
			kRandomConversations = 1 << 1,
			kObserveCombatBehaviour = 1 << 2,
			kGreetCorpseBehaviour = 1 << 3,
			kReactionToPlayerActions = 1 << 4,
			kFriendlyFireComments = 1 << 5,
			kAggroRadiusBehavior = 1 << 6,
			kAllowIdleChatter = 1 << 7,
			kWorldInteractions = 1 << 9
		};

		// members
		stl::enumeration<GeneralFlag, std::uint32_t>           packFlags;              // 0
		stl::enumeration<PACKAGE_PROCEDURE_TYPE, std::uint8_t> packType;               // 4
		stl::enumeration<PACK_INTERRUPT_TARGET, std::uint8_t>  interruptOverrideType;  // 5
		stl::enumeration<PreferredSpeed, std::uint8_t>         maxSpeed;               // 6
		std::uint8_t                                           pad7;                   // 7
		stl::enumeration<InterruptFlag, std::uint16_t>         foBehaviorFlags;        // 8
		std::uint16_t                                          packageSpecificFlags;   // A
	};
	static_assert(sizeof(PACKAGE_DATA) == 0xC);

	class PackageTarget
	{
	public:
		union Target
		{
			inline Target() :
				object(nullptr)
			{}

			~Target() {}

			// members
			ObjectRefHandle                                        handle;
			TESForm*                                               object;
			TESForm*                                               refOrObj;
			stl::enumeration<PACKAGE_OBJECT_TYPE, std::uint32_t>   objType;
			std::uint32_t                                          aliasID;
			stl::enumeration<PACK_INTERRUPT_TARGET, std::uint32_t> interruptTarg;
		};
		static_assert(sizeof(Target) == 0x8);

		// members
		std::int8_t   targType;  // 00
		std::uint8_t  pad01;     // 01
		std::uint16_t pad02;     // 02
		Target        target;    // 08
		std::int32_t  value;     // 10
		std::uint32_t pad14;     // 14
	};
	static_assert(sizeof(PackageTarget) == 0x18);

	struct PACK_SCHED_DATA
	{
		enum class DayOfWeek
		{
			kAny = -1,
			kSunday = 0,
			kMonday = 1,
			kTuesday = 2,
			kWednesday = 3,
			kThursday = 4,
			kFriday = 5,
			kSaturday = 6,
			kWeekdays = 7,
			kWeekends = 8,
			kMondayWednesdayFriday = 9,
			kTuesdayThursday = 10
		};

		// members
		std::int8_t                              month;      // 0
		stl::enumeration<DayOfWeek, std::int8_t> dayOfWeek;  // 1
		std::int8_t                              date;       // 2
		std::int8_t                              hour;       // 3
		std::int8_t                              minute;     // 4
		std::uint8_t                             pad5;       // 5
		std::uint8_t                             pad6;       // 6
		std::uint8_t                             pad7;       // 7
		std::int32_t                             duration;   // 8 - minutes
	};
	static_assert(sizeof(PACK_SCHED_DATA) == 0xC);

	class PackageSchedule  // PSDT
	{
	public:
		// members
		PACK_SCHED_DATA psData;  // 0
	};
	static_assert(sizeof(PackageSchedule) == 0xC);

	class PackageEventAction
	{
	public:
		struct TopicData  // PDTO
		{
			enum class Type
			{
				kTopicRef = 0,
				kTopicSubtype = 1
			};

			// members
			stl::enumeration<Type, std::uint32_t> type;   // 00
			std::uint32_t                         pad04;  // 04
			TESTopic*                             topic;  // 08
		};
		static_assert(sizeof(TopicData) == 0x10);

		// members
		TESIdleForm*                                            idle;   // 00 - INAM
		stl::enumeration<PACK_EVENT_ACTION_TYPE, std::uint32_t> type;   // 08
		std::uint32_t                                           pad0C;  // 0C
		TopicData                                               topic;  // 10 - PDTO
	};
	static_assert(sizeof(PackageEventAction) == 0x20);

	class TESPackage : public TESForm
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESPackage;
		inline static constexpr auto FORMTYPE = FormType::Package;

		struct ChangeFlags
		{
			enum ChangeFlag : std::uint32_t
			{
				kWaitingFlag = 1 << 26,
				kNeverRunFlag = (std::uint32_t)1 << 31
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

		~TESPackage() override;  // 00

		// override (TESForm)
		void          InitializeData() override;                    // 04
		void          ClearData() override;                         // 05
		bool          Load(TESFile* a_mod) override;                // 06
		void          SaveGame(BGSSaveFormBuffer* a_buf) override;  // 0E
		void          LoadGame(BGSLoadFormBuffer* a_buf) override;  // 0F
		void          Revert(BGSLoadFormBuffer* a_buf) override;    // 12
		void          InitItemImpl() override;                      // 13
		std::uint32_t GetRefCount() const override;                 // 2D - { return refCount; }
		[[nodiscard]] const char*   GetObjectTypeName() const override;           // 39 - { return g_packageTypeStrings[packData.packType]; }

		// add
		virtual bool IsActorAtLocation(Actor* a_actor, bool a_arg2, float a_arg3, bool a_arg4);                      // 3B
		virtual bool IsActorAtSecondLocation(Actor* a_arg1, Actor* a_arg2, bool a_arg3, float a_arg4, bool a_arg5);  // 3C
		virtual bool IsActorAtRefTarget(Actor* a_actor, std::int32_t a_arg2);                                        // 3D
		virtual bool IsTargetAtLocation(Actor* a_actor, std::int32_t a_arg2);                                        // 3E
		virtual bool IsPackageOwner(Actor* a_actor);                                                                 // 3F - { return true; }

		// members
		PACKAGE_DATA                                            packData;        // 20 - PKDT
		std::uint32_t                                           pad2C;           // 2C
		TESPackageData*                                         data;            // 30
		PackageLocation*                                        packLoc;         // 38
		PackageTarget*                                          packTarg;        // 40
		BGSIdleCollection*                                      idleCollection;  // 48
		PackageSchedule                                         packSched;       // 50 - PSDT
		std::uint32_t                                           pad5C;           // 5C
		TESCondition                                            packConditions;  // 60
		TESCombatStyle*                                         combatStyle;     // 68 - CNAM
		TESQuest*                                               ownerQuest;      // 70 - QNAM
		PackageEventAction                                      onBegin;         // 78
		PackageEventAction                                      onEnd;           // 98
		PackageEventAction                                      onChange;        // B8
		stl::enumeration<PACKAGE_PROCEDURE_TYPE, std::uint32_t> procedureType;   // D8
		volatile std::uint32_t                                  refCount;        // DC
	};
	static_assert(sizeof(TESPackage) == 0xE0);
}
