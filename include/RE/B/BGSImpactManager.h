#pragma once

#include "RE/N/NiPoint3.h"

namespace RE
{
	class BGSImpactData;
	class BGSImpactDataSet;
	class NiAVObject;
	class TESObjectREFR;

	struct BSSoundHandle;

	struct IMPACT_SOUND_DATA
	{
	public:
		// members
		BGSImpactData* impactData{ nullptr };	   // 00
		NiPoint3*	   position{ nullptr };		   // 08
		NiAVObject*	   objectToFollow{ nullptr };  // 10
		BSSoundHandle* sound1{ nullptr };		   // 18
		BSSoundHandle* sound2{ nullptr };		   // 20
		bool		   playSound1{ false };		   // 28
		bool		   playSound2{ false };		   // 29
		bool		   unk2A{ false };			   // 2A
		void*		   unk30{ nullptr };		   // 30
	};
	static_assert(sizeof(IMPACT_SOUND_DATA) == 0x38);

	class BGSImpactManager
	{
	public:
		static BGSImpactManager* GetSingleton()
		{
			REL::Relocation<BGSImpactManager**> singleton{ REL::ID(515123) };
			return *singleton;
		}

		bool PlayImpactEffect(TESObjectREFR* a_objectReference, BGSImpactDataSet* a_impactEffect, const char* a_nodeName, NiPoint3 a_pickDirection, float a_pickLength, bool a_applyNodeRotation, bool a_useNodeLocalRotation)
		{
			using func_t = decltype(&BGSImpactManager::PlayImpactEffect);
			REL::Relocation<func_t> func{ REL::ID(35320) };
			return func(this, a_objectReference, a_impactEffect, a_nodeName, a_pickDirection, a_pickLength, a_applyNodeRotation, a_useNodeLocalRotation);
		}

		bool PlaySound(IMPACT_SOUND_DATA& a_impactSoundData)
		{
			using func_t = decltype(&BGSImpactManager::PlaySound);
			REL::Relocation<func_t> func{ REL::ID(35317) };
			return func(this, a_impactSoundData);
		}
	};
}
