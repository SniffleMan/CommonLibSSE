#pragma once

#include "RE/B/BSTArray.h"
#include "RE/B/BaseFormComponent.h"
#include "RE/F/FactionRank.h"

namespace RE
{
	class BGSVoiceType;
	class TESActorBase;
	class TESFaction;
	class TESForm;
	class TESLevItem;
	class TESNPC;

	struct ACTOR_BASE_DATA
	{
	public:
		enum class Flag
		{
			kNone = 0,
			kFemale = 1 << 0,
			kEssential = 1 << 1,
			kIsChargenFacePreset = 1 << 2,
			kRespawn = 1 << 3,
			kAutoCalcStats = 1 << 4,
			kUnique = 1 << 5,
			kDoesntAffectStealthMeter = 1 << 6,
			kPCLevelMult = 1 << 7,
			kUsesTemplate = 1 << 8,
			kProtected = 1 << 11,
			kSummonable = 1 << 14,
			kDoesntBleed = 1 << 16,
			kBleedoutOverride = 1 << 18,
			kOppositeGenderanims = 1 << 19,
			kSimpleActor = 1 << 20,
			kLoopedScript = 1 << 21,  // ?
			kLoopedAudio = 1 << 28,   // ?
			kIsGhost = 1 << 29,
			kInvulnerable = 1 << 31
		};

		enum class TEMPLATE_USE_FLAG
		{
			kNone = 0,
			kTraits = 1 << 0,
			kStats = 1 << 1,
			kFactions = 1 << 2,
			kSpells = 1 << 3,
			kAIData = 1 << 4,
			kAIPackages = 1 << 5,
			kUnused = 1 << 6,
			kBaseData = 1 << 7,
			kInventory = 1 << 8,
			kScript = 1 << 9,
			kAIDefPackList = 1 << 10,
			kAttackData = 1 << 11,
			kKeywords = 1 << 12
		};

		// members
		stl::enumeration<Flag, std::uint32_t>              actorBaseFlags;    // 00
		std::int16_t                                       magickaOffset;     // 04
		std::int16_t                                       staminaOffset;     // 06
		std::uint16_t                                      level;             // 08
		std::uint16_t                                      calcLevelMin;      // 0A
		std::uint16_t                                      calcLevelMax;      // 0C
		std::uint16_t                                      speedMult;         // 0E
		std::uint16_t                                      baseDisposition;   // 10 - unused
		stl::enumeration<TEMPLATE_USE_FLAG, std::uint16_t> templateUseFlags;  // 12
		std::int16_t                                       healthOffset;      // 14
		std::int16_t                                       bleedoutOverride;  // 16
	};
	static_assert(sizeof(ACTOR_BASE_DATA) == 0x18);

	class TESActorBaseData : public BaseFormComponent  // ACBS
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESActorBaseData;

		~TESActorBaseData() override;

		// override (BaseFormComponent)
		void InitializeDataComponent() override;                // 01
		void ClearDataComponent() override;                     // 02
		void CopyComponent(BaseFormComponent* a_rhs) override;  // 03

		// add
		virtual void          CopyFromTemplateForms(TESActorBase** a_templateForms);  // 04 - { return; }
		[[nodiscard]] virtual bool          GetIsGhost() const;                                     // 05 - { return (flags >> 29) & 1; }
		[[nodiscard]] virtual bool          GetInvulnerable() const;                                // 06 - { test flags, 80000000h; }
		virtual void          Unk_07(void);                                           // 07 - { return 1; }
		virtual BGSVoiceType* GetVoiceType(void);                                     // 08 - { return voice; }

		[[nodiscard]] constexpr bool AffectsStealthMeter() const noexcept { return actorData.actorBaseFlags.none(ACTOR_BASE_DATA::Flag::kDoesntAffectStealthMeter); }
		[[nodiscard]] constexpr bool Bleeds() const noexcept { return actorData.actorBaseFlags.none(ACTOR_BASE_DATA::Flag::kDoesntBleed); }
		[[nodiscard]] constexpr bool IsEssential() const noexcept { return actorData.actorBaseFlags.all(ACTOR_BASE_DATA::Flag::kEssential); }
		[[nodiscard]] constexpr bool IsFemale() const noexcept { return actorData.actorBaseFlags.all(ACTOR_BASE_DATA::Flag::kFemale); }
		[[nodiscard]] inline bool    IsGhost() const { return GetIsGhost(); }
		[[nodiscard]] constexpr bool IsPreset() const noexcept { return actorData.actorBaseFlags.all(ACTOR_BASE_DATA::Flag::kIsChargenFacePreset); }
		[[nodiscard]] constexpr bool IsProtected() const noexcept { return actorData.actorBaseFlags.all(ACTOR_BASE_DATA::Flag::kProtected); }
		[[nodiscard]] constexpr bool IsSimpleActor() const noexcept { return actorData.actorBaseFlags.all(ACTOR_BASE_DATA::Flag::kSimpleActor); }
		[[nodiscard]] constexpr bool IsSummonable() const noexcept { return actorData.actorBaseFlags.all(ACTOR_BASE_DATA::Flag::kSummonable); }
		[[nodiscard]] constexpr bool IsUnique() const noexcept { return actorData.actorBaseFlags.all(ACTOR_BASE_DATA::Flag::kUnique); }
		[[nodiscard]] inline bool    IsInvulnerable() const { return GetInvulnerable(); }
		[[nodiscard]] constexpr bool HasAutoCalcStats() const noexcept { return actorData.actorBaseFlags.all(ACTOR_BASE_DATA::Flag::kAutoCalcStats); }
		[[nodiscard]] constexpr bool HasBleedoutOverride() const noexcept { return actorData.actorBaseFlags.all(ACTOR_BASE_DATA::Flag::kBleedoutOverride); }
		[[nodiscard]] constexpr bool HasPCLevelMult() const noexcept { return actorData.actorBaseFlags.all(ACTOR_BASE_DATA::Flag::kPCLevelMult); }
		[[nodiscard]] constexpr bool Respawns() const noexcept { return actorData.actorBaseFlags.all(ACTOR_BASE_DATA::Flag::kRespawn); }
		[[nodiscard]] constexpr bool UsesOppositeGenderAnims() const noexcept { return actorData.actorBaseFlags.all(ACTOR_BASE_DATA::Flag::kOppositeGenderanims); }
		[[nodiscard]] constexpr bool UsesTemplate() const noexcept { return actorData.actorBaseFlags.all(ACTOR_BASE_DATA::Flag::kUsesTemplate); }

		// members
		ACTOR_BASE_DATA        actorData;         // 08
		TESLevItem*            deathItem;         // 20 - INAM
		BGSVoiceType*          voiceType;         // 28 - VTCK
		TESForm*               baseTemplateForm;  // 30 - TPLT
		TESForm**              templateForms;     // 38
		BSTArray<FACTION_RANK> factions;          // 40
	};
	static_assert(sizeof(TESActorBaseData) == 0x58);
}
