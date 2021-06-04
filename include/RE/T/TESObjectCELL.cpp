#include "RE/T/TESObjectCELL.h"

#include "RE/B/BGSEncounterZone.h"
#include "RE/E/ExtraNorthRotation.h"
#include "RE/T/TESFaction.h"
#include "RE/T/TESNPC.h"
#include "RE/T/TESWorldSpace.h"

namespace RE
{
	void TESObjectCELL::ForEachReference(std::function<bool(RE::TESObjectREFR&)> a_callback) const
	{
		BSSpinLockGuard locker(spinLock);
		for (const auto& ref : references) {
			if (ref && !a_callback(*ref)) {
				break;
			}
		}
	}

	void TESObjectCELL::ForEachReferenceInRange(const NiPoint3& a_origin, float a_radius, std::function<bool(TESObjectREFR&)> a_callback) const
	{
		ForEachReference([&](TESObjectREFR& ref) {
			const auto distance = a_origin.GetSquaredDistance(ref.GetPosition());
			return distance <= a_radius ?
						 a_callback(ref) :
						 true;
		});
	}

	TESNPC* TESObjectCELL::GetActorOwner()
	{
		auto owner = GetOwner();
		return owner && owner->Is(FormType::NPC) ? static_cast<TESNPC*>(owner) : nullptr;
	}

	EXTERIOR_DATA* TESObjectCELL::GetCoordinates()
	{
		return IsExteriorCell() ? cellData.exterior : nullptr;
	}

	TESFaction* TESObjectCELL::GetFactionOwner()
	{
		auto owner = GetOwner();
		return owner && owner->Is(FormType::Faction) ? static_cast<TESFaction*>(owner) : nullptr;
	}

	INTERIOR_DATA* TESObjectCELL::GetLighting()
	{
		return IsInteriorCell() ? cellData.interior : nullptr;
	}

	float TESObjectCELL::GetNorthRotation()
	{
		if (IsExteriorCell()) {
			return worldSpace->northRotation;
		} else {
			auto xNorth = extraList.GetByType<ExtraNorthRotation>();
			return xNorth ? xNorth->northRot : static_cast<float>(0.0);
		}
	}

	TESForm* TESObjectCELL::GetOwner()
	{
		auto owner = extraList.GetOwner();
		if (owner) {
			return owner;
		}

		BGSEncounterZone* zone = nullptr;
		if (loadedData) {
			zone = loadedData->encounterZone;
		} else {
			zone = extraList.GetEncounterZone();
			if (!zone && IsExteriorCell()) {
				zone = worldSpace ? worldSpace->encounterZone : nullptr;
			}
		}

		return zone ? zone->data.zoneOwner : nullptr;
	}

	bool TESObjectCELL::IsAttached() const
	{
		return cellState == CellState::kAttached;
	}

	bool TESObjectCELL::IsExteriorCell() const
	{
		return !IsInteriorCell();
	}

	bool TESObjectCELL::IsInteriorCell() const
	{
		return cellFlags.all(Flag::kIsInteriorCell);
	}

	void TESObjectCELL::SetActorOwner(TESNPC* a_owner)
	{
		SetOwner(a_owner);
	}

	void TESObjectCELL::SetFactionOwner(TESFaction* a_owner)
	{
		SetOwner(a_owner);
	}

	void TESObjectCELL::SetFogColor(Color a_near, Color a_far)
	{
		if (!UsesSkyLighting()) {
			auto lighting = GetLighting();
			if (lighting) {
				lighting->fogColorNear = a_near;
				lighting->fogColorFar = a_far;
			}
		}
	}

	void TESObjectCELL::SetFogPlanes(float a_near, float a_far)
	{
		if (!UsesSkyLighting()) {
			auto lighting = GetLighting();
			if (lighting) {
				lighting->fogNear = a_near;
				lighting->fogFar = a_far;
			}
		}
	}

	void TESObjectCELL::SetFogPower(float a_power)
	{
		if (!UsesSkyLighting()) {
			auto lighting = GetLighting();
			if (lighting) {
				lighting->fogPower = a_power;
			}
		}
	}

	void TESObjectCELL::SetHandChanged(bool a_changed)
	{
		if (a_changed) {
			cellFlags.set(Flag::kHandChanged);
		} else {
			cellFlags.reset(Flag::kHandChanged);
		}
		AddChange(ChangeFlags::kFlags);
	}

	void TESObjectCELL::SetOwner(TESForm* a_owner)
	{
		extraList.SetOwner(a_owner);
		AddChange(ChangeFlags::kOwnership);
	}

	void TESObjectCELL::SetPublic(bool a_public)
	{
		if (a_public) {
			cellFlags.set(Flag::kPublicArea);
		} else {
			cellFlags.reset(Flag::kPublicArea);
		}
		AddChange(ChangeFlags::kFlags);
	}

	bool TESObjectCELL::UsesSkyLighting() const
	{
		return cellFlags.all(Flag::kUseSkyLighting);
	}
}
