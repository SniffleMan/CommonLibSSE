#include "RE/A/Actor.h"

#include "RE/A/AIProcess.h"
#include "RE/B/BGSAttackData.h"
#include "RE/B/BGSColorForm.h"
#include "RE/B/BGSDefaultObjectManager.h"
#include "RE/B/BSFaceGenAnimationData.h"
#include "RE/E/ExtraCanTalkToPlayer.h"
#include "RE/E/ExtraFactionChanges.h"
#include "RE/F/FormTraits.h"
#include "RE/H/HighProcessData.h"
#include "RE/I/InventoryEntryData.h"
#include "RE/M/MiddleHighProcessData.h"
#include "RE/M/Misc.h"
#include "RE/N/NiColor.h"
#include "RE/N/NiNode.h"
#include "RE/N/NiPoint3.h"
#include "RE/P/ProcessLists.h"
#include "RE/T/TESFaction.h"
#include "RE/T/TESNPC.h"
#include "RE/T/TESObjectMISC.h"
#include "RE/T/TESRace.h"
#include "RE/T/TESWorldSpace.h"

namespace RE
{
	NiPointer<Actor> Actor::LookupByHandle(RefHandle a_refHandle)
	{
		NiPointer<Actor> ref;
		LookupReferenceByHandle(a_refHandle, ref);
		return ref;
	}

	bool Actor::LookupByHandle(RefHandle a_refHandle, NiPointer<Actor>& a_refrOut)
	{
		return LookupReferenceByHandle(a_refHandle, a_refrOut);
	}

	bool Actor::AddSpell(SpellItem* a_spell)
	{
		using func_t = decltype(&Actor::AddSpell);
		REL::Relocation<func_t> func{ Offset::Actor::AddSpell };
		return func(this, a_spell);
	}

	void Actor::AllowBleedoutDialogue(bool a_canTalk)
	{
		if (a_canTalk) {
			boolFlags.set(BOOL_FLAGS::kCanSpeakToEssentialDown);
		} else {
			boolFlags.reset(BOOL_FLAGS::kCanSpeakToEssentialDown);
		}
	}

	void Actor::AllowPCDialogue(bool a_talk)
	{
		auto xTalk = extraList.GetByType<ExtraCanTalkToPlayer>();
		if (!xTalk) {
			xTalk = new ExtraCanTalkToPlayer();
			extraList.Add(xTalk);
		}

		xTalk->talk = a_talk;
	}

	bool Actor::CanFlyHere() const
	{
		const auto* worldSpace = GetWorldspace();
		return worldSpace && worldSpace->HasMaxHeightData();
	}

	bool Actor::CanPickpocket() const
	{
		if (!race) {
			return false;
		}

		return race->AllowsPickpocket() && !IsPlayerTeammate();
	}

	bool Actor::CanTalkToPlayer() const
	{
		auto xTalk = extraList.GetByType<ExtraCanTalkToPlayer>();
		if (xTalk) {
			return xTalk->talk;
		} else {
			return race ? race->AllowsPCDialogue() : false;
		}
	}

	void Actor::ClearArrested()
	{
		if (currentProcess && currentProcess->IsArrested()) {
			currentProcess->SetArrested(false);
			EvaluatePackage(false, false);
			auto procManager = ProcessLists::GetSingleton();
			if (procManager) {
				procManager->StopCombatAndAlarmOnActor(this, true);
			}
		}
	}

	void Actor::ClearExpressionOverride()
	{
		auto faceGen = GetFaceGenAnimationData();
		if (faceGen) {
			faceGen->ClearExpressionOverride();
		}
	}

	ActorHandle Actor::CreateRefHandle()
	{
		return GetHandle();
	}

	void Actor::DispelWornItemEnchantments()
	{
		using func_t = decltype(&Actor::DispelWornItemEnchantments);
		REL::Relocation<func_t> func{ Offset::Actor::DispelWornItemEnchantments };
		return func(this);
	}

	void Actor::DoReset3D(bool a_updateWeight)
	{
		using func_t = decltype(&Actor::DoReset3D);
		REL::Relocation<func_t> func{ Offset::Actor::DoReset3D };
		return func(this, a_updateWeight);
	}

	void Actor::EvaluatePackage(bool a_immediate, bool a_resetAI)
	{
		using func_t = decltype(&Actor::EvaluatePackage);
		REL::Relocation<func_t> func{ REL::ID(36407) };
		return func(this, a_immediate, a_resetAI);
	}

	TESNPC* Actor::GetActorBase()
	{
		auto obj = GetBaseObject();
		return obj ? obj->As<TESNPC>() : nullptr;
	}

	const TESNPC* Actor::GetActorBase() const
	{
		auto obj = GetBaseObject();
		return obj ? obj->As<TESNPC>() : nullptr;
	}

	InventoryEntryData* Actor::GetAttackingWeapon()
	{
		if (!currentProcess || !currentProcess->high || !currentProcess->high->attackData || !currentProcess->middleHigh) {
			return nullptr;
		}

		auto attackData = currentProcess->high->attackData;
		auto proc = currentProcess->middleHigh;

		return attackData->IsLeftAttack() ? proc->leftHand : proc->rightHand;
	}

	const InventoryEntryData* Actor::GetAttackingWeapon() const
	{
		if (!currentProcess || !currentProcess->high || !currentProcess->high->attackData || !currentProcess->middleHigh) {
			return nullptr;
		}

		auto attackData = currentProcess->high->attackData;
		auto proc = currentProcess->middleHigh;

		return attackData->IsLeftAttack() ? proc->leftHand : proc->rightHand;
	}

	bhkCharacterController* Actor::GetCharController() const
	{
		return currentProcess ? currentProcess->GetCharController() : nullptr;
	}

	ActorHandle Actor::GetCommandingActor() const
	{
		return currentProcess ? currentProcess->GetCommandingActor() : ActorHandle{};
	}

	TESFaction* Actor::GetCrimeFaction()
	{
		return GetCrimeFactionImpl();
	}

	const TESFaction* Actor::GetCrimeFaction() const
	{
		return GetCrimeFactionImpl();
	}

	InventoryEntryData* Actor::GetEquippedEntryData(bool a_leftHand) const
	{
		if (!currentProcess || !currentProcess->middleHigh) {
			return nullptr;
		}

		auto proc = currentProcess->middleHigh;
		if (proc->bothHands) {
			return proc->bothHands;
		} else {
			return a_leftHand ? proc->leftHand : proc->rightHand;
		}
	}

	TESForm* Actor::GetEquippedObject(bool a_leftHand) const
	{
		if (currentProcess) {
			if (a_leftHand) {
				return currentProcess->GetEquippedLeftHand();
			} else {
				return currentProcess->GetEquippedRightHand();
			}
		} else {
			return nullptr;
		}
	}

	std::int32_t Actor::GetGoldAmount()
	{
		const auto inv = GetInventory([](TESBoundObject& a_object) -> bool {
			return a_object.IsGold();
		});

		const auto dobj = BGSDefaultObjectManager::GetSingleton();
		if (!dobj) {
			return 0;
		}

		const auto gold = dobj->GetObject<TESObjectMISC>(DEFAULT_OBJECT::kGold);
		const auto it = inv.find(gold);
		return it != inv.end() ? it->second.first : 0;
	}

	ActorHandle Actor::GetHandle()
	{
		return ActorHandle(this);
	}

	float Actor::GetHeight()
	{
		const auto min = GetBoundMin();
		const auto max = GetBoundMax();
		const auto diff = max.z - min.z;
		const auto height = GetBaseHeight() * diff;

		if (!currentProcess || !currentProcess->InHighProcess()) {
			return height;
		}

		const auto cachedHeight = currentProcess->GetCachedHeight();
		if (cachedHeight == 0.0) {
			currentProcess->SetCachedHeight(height);
			return height;
		} else {
			return cachedHeight;
		}
	}

	std::uint16_t Actor::GetLevel() const
	{
		using func_t = decltype(&Actor::GetLevel);
		REL::Relocation<func_t> func{ Offset::Actor::GetLevel };
		return func(this);
	}

	ObjectRefHandle Actor::GetOccupiedFurniture() const
	{
		if (currentProcess) {
			return currentProcess->GetOccupiedFurniture();
		} else {
			return {};
		}
	}

	TESRace* Actor::GetRace() const
	{
		auto base = GetActorBase();
		return base ? base->race : nullptr;
	}

	bool Actor::HasPerk(BGSPerk* a_perk) const
	{
		using func_t = decltype(&Actor::HasPerk);
		REL::Relocation<func_t> func{ Offset::Actor::HasPerk };
		return func(this, a_perk);
	}

	void Actor::InterruptCast(bool a_restoreMagicka) const
	{
		using func_t = decltype(&Actor::InterruptCast);
		REL::Relocation<func_t> func{ REL::ID(37808) };
		return func(this, a_restoreMagicka);
	}

	bool Actor::IsAIEnabled() const
	{
		return boolBits.all(BOOL_BITS::kProcessMe);
	}

	bool Actor::IsAMount() const
	{
		return boolFlags.all(BOOL_FLAGS::kIsAMount);
	}

	bool Actor::IsAnimationDriven() const
	{
		bool result = false;
		return GetGraphVariableBool("bAnimationDriven", result) && result;
	}

	bool Actor::IsBeingRidden() const
	{
		return IsAMount() && extraList.HasType(ExtraDataType::kInteraction);
	}

	bool Actor::IsCommandedActor() const
	{
		return boolFlags.all(BOOL_FLAGS::kIsCommandedActor);
	}

	bool Actor::IsEssential() const
	{
		return boolFlags.all(BOOL_FLAGS::kEssential);
	}

	bool Actor::IsFactionInCrimeGroup(const TESFaction* a_faction) const
	{
		auto crimFac = GetCrimeFaction();
		if (!crimFac) {
			return false;
		}

		if (crimFac == a_faction) {
			return true;
		} else {
			return crimFac->IsFactionInCrimeGroup(a_faction);
		}
	}

	bool Actor::IsGhost() const
	{
		using func_t = decltype(&Actor::IsGhost);
		REL::Relocation<func_t> func{ Offset::Actor::GetGhost };
		return func(this);
	}

	bool Actor::IsGuard() const
	{
		return boolBits.all(BOOL_BITS::kGuard);
	}

	bool Actor::IsHostileToActor(Actor* a_actor)
	{
		using func_t = decltype(&Actor::IsHostileToActor);
		REL::Relocation<func_t> func{ Offset::Actor::GetHostileToActor };
		return func(this, a_actor);
	}

	bool Actor::IsOnMount() const
	{
		return !IsAMount() && extraList.HasType(ExtraDataType::kInteraction);
	}

	bool Actor::IsPlayerTeammate() const
	{
		return boolBits.all(BOOL_BITS::kPlayerTeammate);
	}
	

	bool Actor::IsPowerAttacking() const
	{
		if (!this->currentProcess || !this->currentProcess->high)
			return false;

		auto attackData = this->currentProcess->high->attackData;

		if (attackData)
			return attackData->data.flags.any(RE::AttackData::AttackFlag::kPowerAttack);
		else
			return false;
	}

	bool Actor::IsRunning() const
	{
		using func_t = decltype(&Actor::IsRunning);
		REL::Relocation<func_t> func{ Offset::Actor::IsRunning };
		return func(this);
	}

	bool Actor::IsSneaking() const
	{
		if (!ActorState::IsSneaking()) {
			return false;
		}

		if (ActorState::IsSwimming()) {
			return false;
		}

		if (IsOnMount()) {
			return false;
		}

		return true;
	}
	

	bool Actor::IsStaggering() const
	{
		bool result = false;
		this->GetGraphVariableBool("IsStaggering", result);
		return result;
	}

	bool Actor::IsSummoned() const noexcept
	{
		return currentProcess && currentProcess->GetIsSummonedCreature();
	}

	bool Actor::IsTrespassing() const
	{
		return boolFlags.all(BOOL_FLAGS::kIsTrespassing);
	}

	void Actor::RemoveExtraArrows3D()
	{
		extraList.RemoveByType(ExtraDataType::kAttachedArrows3D);
	}

	bool Actor::RemoveSpell(SpellItem* a_spell)
	{
		using func_t = decltype(&Actor::RemoveSpell);
		REL::Relocation<func_t> func{ REL::ID(37772) };
		return func(this, a_spell);
	}

	std::int32_t Actor::RequestDetectionLevel(Actor* a_target, DETECTION_PRIORITY a_priority)
	{
		using func_t = decltype(&Actor::RequestDetectionLevel);
		REL::Relocation<func_t> func{ Offset::Actor::RequestDetectionLevel };
		return func(this, a_target, a_priority);
	}

	void Actor::StealAlarm(TESObjectREFR* a_ref, TESForm* a_object, std::int32_t a_num, std::int32_t a_total, TESForm* a_owner, bool a_allowWarning)
	{
		using func_t = decltype(&Actor::StealAlarm);
		REL::Relocation<func_t> func{ REL::ID(36427) };
		return func(this, a_ref, a_object, a_num, a_total, a_owner, a_allowWarning);
	}

	void Actor::SwitchRace(TESRace* a_race, bool a_player)
	{
		using func_t = decltype(&Actor::SwitchRace);
		REL::Relocation<func_t> func{ Offset::Actor::SwitchRace };
		return func(this, a_race, a_player);
	}

	void Actor::UpdateArmorAbility(TESForm* a_armor, ExtraDataList* a_extraData)
	{
		using func_t = decltype(&Actor::UpdateArmorAbility);
		REL::Relocation<func_t> func{ Offset::Actor::UpdateArmorAbility };
		return func(this, a_armor, a_extraData);
	}

	void Actor::Update3DModel()
	{
		if (currentProcess) {
			currentProcess->Update3DModel(this);
		}
	}

	void Actor::UpdateHairColor()
	{
		auto npc = GetActorBase();
		if (npc && npc->headRelatedData) {
			const auto hairColor = npc->headRelatedData->hairColor;
			if (hairColor) {
				NiColor color;
				color.red = hairColor->color.red / static_cast<float>(128.0);
				color.green = hairColor->color.green / static_cast<float>(128.0);
				color.blue = hairColor->color.blue / static_cast<float>(128.0);

				auto model = Get3D(false);
				if (model) {
					model->UpdateHairColor(color);
				}
			}
		}
	}

	void Actor::UpdateSkinColor()
	{
		const auto* npc = GetActorBase();
		if (npc) {
			NiColor color;
			color.red = npc->bodyTintColor.red / static_cast<float>(255.0);
			color.green = npc->bodyTintColor.green / static_cast<float>(255.0);
			color.blue = npc->bodyTintColor.blue / static_cast<float>(255.0);

			auto thirdPerson = Get3D(false);
			if (thirdPerson) {
				thirdPerson->UpdateBodyTint(color);
			}

			auto firstPerson = Get3D(true);
			if (firstPerson) {
				firstPerson->UpdateBodyTint(color);
			}
		}
	}

	void Actor::UpdateWeaponAbility(TESForm* a_weapon, ExtraDataList* a_extraData, bool a_leftHand)
	{
		using func_t = decltype(&Actor::UpdateWeaponAbility);
		REL::Relocation<func_t> func{ Offset::Actor::UpdateWeaponAbility };
		return func(this, a_weapon, a_extraData, a_leftHand);
	}

	bool Actor::VisitFactions(std::function<bool(TESFaction* a_faction, std::int8_t a_rank)> a_visitor)
	{
		auto base = GetActorBase();
		if (base) {
			for (auto& factionInfo : base->factions) {
				if (a_visitor(factionInfo.faction, factionInfo.rank)) {
					return true;
				}
			}

			auto factionChanges = extraList.GetByType<ExtraFactionChanges>();
			if (factionChanges) {
				for (auto& change : factionChanges->factionChanges) {
					if (a_visitor(change.faction, change.rank)) {
						return true;
					}
				}
			}
		}

		return false;
	}

	bool Actor::WouldBeStealing(const TESObjectREFR* a_target) const
	{
		return a_target ? !a_target->IsAnOwner(this, true, false) : false;
	}

	TESFaction* Actor::GetCrimeFactionImpl() const
	{
		if (IsCommandedActor()) {
			return nullptr;
		}

		auto xFac = extraList.GetByType<ExtraFactionChanges>();
		if (xFac && (xFac->crimeFaction || xFac->removeCrimeFaction)) {
			return xFac->crimeFaction;
		}

		auto base = GetActorBase();
		return base ? base->crimeFaction : nullptr;
	}
}
