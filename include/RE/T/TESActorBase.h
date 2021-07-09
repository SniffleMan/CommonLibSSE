#pragma once

#include "RE/A/ActorValueOwner.h"
#include "RE/B/BGSAttackDataForm.h"
#include "RE/B/BGSDestructibleObjectForm.h"
#include "RE/B/BGSKeywordForm.h"
#include "RE/B/BGSPerkRankArray.h"
#include "RE/B/BGSSkinForm.h"
#include "RE/F/FormTypes.h"
#include "RE/T/TESAIForm.h"
#include "RE/T/TESActorBaseData.h"
#include "RE/T/TESBoundAnimObject.h"
#include "RE/T/TESContainer.h"
#include "RE/T/TESFullName.h"
#include "RE/T/TESSpellList.h"

namespace RE
{
	class TESActorBase :
		public TESBoundAnimObject,         // 000
		public TESActorBaseData,           // 030
		public TESContainer,               // 088
		public TESSpellList,               // 0A0
		public TESAIForm,                  // 0B0
		public TESFullName,                // 0D8
		public ActorValueOwner,            // 0E8
		public BGSDestructibleObjectForm,  // 0F0
		public BGSSkinForm,                // 100
		public BGSKeywordForm,             // 110
		public BGSAttackDataForm,          // 128
		public BGSPerkRankArray            // 138
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESActorBase;

		~TESActorBase() override;  // 00

		// override (TESBoundAnimObject)
		bool AddChange(std::uint32_t a_changeFlags) override;     // 0A
		void RemoveChange(std::uint32_t a_changeFlags) override;  // 0B
		void SaveGame(BGSSaveFormBuffer* a_buf) override;         // 0E
		void LoadGame(BGSLoadFormBuffer* a_buf) override;         // 0F
		bool IsAutoCalc() const override;                         // 3E - { return formType == FormType::NPC && (TESActorBaseData::flags >> 4) & 1; }
		void SetAutoCalc(bool a_autoCalc) override;               // 3F

		// override (TESAIForm)
		float GetActorValue(ActorValue a_akValue) override;                                                      // 01
		float GetPermanentActorValue(ActorValue a_akValue) override;                                             // 02
		float GetBaseActorValue(ActorValue a_akValue) override;                                                  // 03
		void  SetBaseActorValue(ActorValue a_akValue, float a_value) override;                                   // 04
		void  ModActorValue(ActorValue a_akValue, float a_value) override;                                       // 05
		void  RestoreActorValue(ACTOR_VALUE_MODIFIER a_modifier, ActorValue a_akValue, float a_value) override;  // 06
		void  SetActorValue(ActorValue a_akValue, float a_value) override;                                       // 07
		[[nodiscard]] bool  GetIsPlayerOwner() const override;                                                                 // 08

		// add
		[[nodiscard]] virtual bool            GetHasPLSpecTex() const;                        // 53 - { return false; }
		virtual TESCombatStyle* GetCombatStyle();                               // 54 - { return 0; }
		virtual void            SetCombatStyle(TESCombatStyle* a_combatStyle);  // 55 - { return; }
		virtual TESForm*        GetAsForm();                                    // 56 - { return this; }
	};
	static_assert(sizeof(TESActorBase) == 0x150);
}
