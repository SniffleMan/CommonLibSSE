#pragma once

namespace RE
{
	class TESObjectREFR;

	struct BGSDecalGroup;
	struct DECAL_CREATION_DATA;

	class BGSDecalManager
	{
	public:
		static BGSDecalManager* GetSingleton()
		{
			REL::Relocation<BGSDecalManager**> singleton{ REL::ID(514414) };
			return *singleton;
		}

		static bool IsApplyingDecal()
		{
			REL::Relocation<bool*> isApplyingDecal{ REL::ID(525040) };
			return *isApplyingDecal;
		}

		static void SetApplyingDecal(bool a_isApplyingDecal)
		{
			using func_t = decltype(&BGSDecalManager::SetApplyingDecal);
			REL::Relocation<func_t> func{ REL::ID(76070) };
			return func(a_isApplyingDecal);
		}

		static bool ShouldApplyDecal(RE::TESObjectREFR* a_objectReference)
		{
			using func_t = decltype(&BGSDecalManager::ShouldApplyDecal);
			REL::Relocation<func_t> func{ REL::ID(15044) };
			return func(a_objectReference);
		}

		void ApplyDecal(RE::DECAL_CREATION_DATA& a_decalCreationData, bool a_forceDecal, RE::BGSDecalGroup* a_decalGroup)
		{
			using func_t = decltype(&BGSDecalManager::ApplyDecal);
			REL::Relocation<func_t> func{ REL::ID(15029) };
			return func(this, a_decalCreationData, a_forceDecal, a_decalGroup);
		}

		// members
		std::uint32_t unk00;					   // 00
		std::uint32_t decalCountCurrentFrame;	   // 04
		std::uint32_t skinDecalCountCurrentFrame;  // 08
		std::uint32_t decalCount;				   // 0C
		std::uint32_t skinDecalCount;			   // 10
		bool		  unk14;					   // 14
	};
	static_assert(sizeof(BGSDecalManager) == 0x18);
}
