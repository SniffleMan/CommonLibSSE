#pragma once

#include "RE/A/AITimeStamp.h"
#include "RE/B/BSFixedString.h"
#include "RE/B/BSTHashMap.h"
#include "RE/B/BSTList.h"
#include "RE/F/FightReactions.h"
#include "RE/F/FormTypes.h"
#include "RE/T/TESForm.h"
#include "RE/T/TESFullName.h"
#include "RE/T/TESReactionForm.h"
#include "RE/T/TESTexture.h"

namespace RE
{
	class TESCondition;
	class PackageLocation;

	struct FACTION_DATA
	{
		enum Flag : std::uint32_t
		{
			kNone = 0,
			kHiddenFromNPC = 1 << 0,
			kSpecialCombat = 1 << 1,
			kPlayerIsExpelled = 1 << 2,
			kPlayerIsEnemy = 1 << 3,
			kTrackCrime = 1 << 6,
			kIgnoresCrimes_Murder = 1 << 7,
			kIgnoresCrimes_Assult = 1 << 8,
			kIgnoresCrimes_Stealing = 1 << 9,
			kIngoresCrimes_Trespass = 1 << 10,
			kDoNotReportCrimesAgainstMembers = 1 << 11,
			kCrimeGold_UseDefaults = 1 << 12,
			kIgnoresCrimes_Pickpocket = 1 << 13,
			kVendor = 1 << 14,
			kCanBeOwner = 1 << 15,
			kIgnoresCrimes_Werewolf = 1 << 16
		};

		Flag flags;  // 0
	};
	static_assert(sizeof(FACTION_DATA) == 0x4);

	struct FACTION_CRIME_DATA_VALUES  // CRVA
	{
	public:
		// members
		bool          arrest;               // 00
		bool          attackOnSight;        // 01
		std::uint16_t murderCrimeGold;      // 02
		std::uint16_t assaultCrimeGold;     // 04
		std::uint16_t trespassCrimeGold;    // 06
		std::uint16_t pickpocketCrimeGold;  // 08
		std::uint16_t pad0A;                // 0A
		float         stealCrimeGoldMult;   // 0C
		std::uint16_t escapeCrimeGold;      // 10
		std::uint16_t werewolfCrimeGold;    // 12
	};
	static_assert(sizeof(FACTION_CRIME_DATA_VALUES) == 0x14);

	struct FACTION_CRIME_DATA
	{
	public:
		// members
		TESObjectREFR*            factionJailMarker;                // 00 - JAIL
		TESObjectREFR*            factionWaitMarker;                // 08 - WAIT
		TESObjectREFR*            factionStolenContainer;           // 10 - STOL
		TESObjectREFR*            factionPlayerInventoryContainer;  // 18 - PLCN
		BGSListForm*              crimeGroup;                       // 20 - CRGR
		BGSOutfit*                jailOutfit;                       // 28 - JOUT
		FACTION_CRIME_DATA_VALUES crimevalues;                      // 30 - CRVA
		std::uint32_t             pad44;                            // 44
	};
	static_assert(sizeof(FACTION_CRIME_DATA) == 0x48);

	struct FACTION_VENDOR_DATA_VALUES  // VENV
	{
	public:
		// members
		std::uint16_t startHour;       // 0
		std::uint16_t endHour;         // 2
		std::uint32_t locationRadius;  // 4
		bool          buysStolen;      // 8
		bool          notBuySell;      // 9
		bool          buysNonStolen;   // A
		std::uint8_t  padB;            // B
	};
	static_assert(sizeof(FACTION_VENDOR_DATA_VALUES) == 0xC);

	struct FACTION_VENDOR_DATA  // VENV
	{
	public:
		// members
		FACTION_VENDOR_DATA_VALUES vendorValues;       // 00
		std::uint32_t              pad0C;              // 0C
		PackageLocation*           vendorLocation;     // 10 - PLVD
		TESCondition*              vendorConditions;   // 18
		BGSListForm*               vendorSellBuyList;  // 20 - VEND
		TESObjectREFR*             merchantContainer;  // 28 - VENC
		std::uint32_t              lastDayReset;       // 30
		std::uint32_t              pad34;              // 34
	};
	static_assert(sizeof(FACTION_VENDOR_DATA) == 0x38);

	struct RANK_DATA
	{
	public:
		// members
		BSFixedString maleRankTitle;    // 00 - MNAM
		BSFixedString femaleRankTitle;  // 08 - FNAM
		TESTexture    textureInsignia;  // 10 - INAM - unused
	};
	static_assert(sizeof(RANK_DATA) == 0x20);

	class TESFaction :
		public TESForm,         // 000
		public TESFullName,     // 020
		public TESReactionForm  // 030
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESFaction;
		inline static constexpr auto FORMTYPE = FormType::Faction;

		struct ChangeFlags
		{
			enum ChangeFlag : std::uint32_t
			{
				kFactionFlags = 1 << 1,
				kFactionReactions = 1 << 2,
				kFactionCrimeCounts = (std::uint32_t)1 << 31
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

		~TESFaction() override;  // 00

		// override (TESForm)
		void InitializeData() override;                    // 04
		void ClearData() override;                         // 05
		bool Load(TESFile* a_mod) override;                // 06
		void SaveGame(BGSSaveFormBuffer* a_buf) override;  // 0E
		void LoadGame(BGSLoadFormBuffer* a_buf) override;  // 0F
		void Revert(BGSLoadFormBuffer* a_buf) override;    // 12
		void InitItemImpl() override;                      // 13

		[[nodiscard]] bool         CanBeOwner() const;
		[[nodiscard]] bool         CanPayCrimeGold() const;
		[[nodiscard]] std::int32_t GetCrimeGold() const;
		[[nodiscard]] std::int32_t GetCrimeGoldNonViolent() const;
		[[nodiscard]] std::int32_t GetCrimeGoldViolent() const;
		[[nodiscard]] std::int32_t GetInfamy() const;
		[[nodiscard]] std::int32_t GetInfamyNonViolent() const;
		[[nodiscard]] std::int32_t GetInfamyViolent() const;
		[[nodiscard]] std::int32_t GetStolenItemValueCrime() const;
		[[nodiscard]] std::int32_t GetStolenItemValueNoCrime() const;
		[[nodiscard]] bool         HasSpecialCombatState() const;
		[[nodiscard]] bool         HasStealMultiplier() const;
		[[nodiscard]] bool         HiddenFromNPC() const;
		[[nodiscard]] bool         IgnoresAssault() const;
		[[nodiscard]] bool         IgnoresMurder() const;
		[[nodiscard]] bool         IgnoresPickpocket() const;
		[[nodiscard]] bool         IgnoresStealing() const;
		[[nodiscard]] bool         IgnoresTrespass() const;
		[[nodiscard]] bool         IgnoresWerewolf() const;
		bool         IsFactionInCrimeGroup(const TESFaction* a_other) const;
		[[nodiscard]] bool         IsPlayerEnemy() const;
		[[nodiscard]] bool         IsPlayerExpelled() const;
		[[nodiscard]] bool         IsVendor() const;
		void         ModCrimeGold(std::int32_t a_amount, bool a_violent);
		void         PlayerPayCrimeGold(bool a_removeStolenItems = true, bool a_goToJail = true);
		[[nodiscard]] bool         ReportsCrimesAgainstMembers() const;
		void         SendPlayerToJail(bool a_removeInventory = true, bool a_realJail = true);
		void         SetAlly(TESFaction* a_other, bool a_selfIsFriendToOther = false, bool a_otherIsFriendToSelf = false);
		void         SetCrimeGold(std::int32_t a_gold);
		void         SetCrimeGoldViolent(std::int32_t a_gold);
		void         SetEnemy(TESFaction* a_other, bool a_selfIsNeutralToOther = false, bool a_otherIsNeutralToSelf = false);
		void         SetFactionFightReaction(TESFaction* a_faction, FIGHT_REACTION a_fightReaction);
		[[nodiscard]] bool         TracksCrimes() const;
		[[nodiscard]] bool         UsesCrimeGoldDefaults() const;

		// members
		BSTHashMap<const TESNPC*, std::uint32_t>* crimeGoldMap;           // 050
		FACTION_DATA                              data;                   // 058 - DATA
		std::uint32_t                             pad05C;                 // 05C
		FACTION_CRIME_DATA                        crimeData;              // 060
		FACTION_VENDOR_DATA                       vendorData;             // 0A8
		BSSimpleList<RANK_DATA*>                  rankData;               // 0E0
		std::int32_t                              majorCrime;             // 0F0
		std::int32_t                              minorCrime;             // 0F4
		AITimeStamp                               resistArrestTimeStamp;  // 0F8
		float                                     pcEnemyFlagTimeStamp;   // 0FC - current game time in hours
	};
	static_assert(sizeof(TESFaction) == 0x100);
}
