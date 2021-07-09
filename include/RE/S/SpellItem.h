#pragma once

#include "RE/B/BGSEquipType.h"
#include "RE/B/BGSMenuDisplayObject.h"
#include "RE/F/FormTypes.h"
#include "RE/M/MagicItem.h"
#include "RE/T/TESDescription.h"

namespace RE
{
	class SpellItem :
		public MagicItem,             // 00
		public BGSEquipType,          // 90
		public BGSMenuDisplayObject,  // A0
		public TESDescription         // B0
	{
	public:
		inline static constexpr auto RTTI = RTTI_SpellItem;
		inline static constexpr auto FORMTYPE = FormType::Spell;

		enum class SpellFlag
		{
			kNone = 0,
			kCostOverride = 1 << 0,
			kFoodItem = 1 << 1,
			kExtendDuration = 1 << 3,
			kPCStartSpell = 1 << 17,
			kInstantCast = 1 << 18,
			kIgnoreLOSCheck = 1 << 19,
			kIgnoreResistance = 1 << 20,
			kNoAbsorb = 1 << 21,
			kNoDualCastMods = 1 << 23
		};

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		class Data  // SPIT
		{
		public:
			// members
			std::int32_t                               costOverride;  // 00
			stl::enumeration<SpellFlag, std::uint32_t> flags;         // 04
			MagicSystem::SpellType                     spellType;     // 08
			float                                      chargeTime;    // 0C
			MagicSystem::CastingType                   castingType;   // 10
			MagicSystem::Delivery                      delivery;      // 14
			float                                      castDuration;  // 18
			float                                      range;         // 1C
			BGSPerk*                                   castingPerk;   // 20
		};
		static_assert(sizeof(Data) == 0x28);

		~SpellItem() override;  // 00

		// override (MagicItem)
		void                     InitializeData() override;                                             // 04
		void                     ClearData() override;                                                  // 05
		void                     InitItemImpl() override;                                               // 13
		MagicSystem::SpellType   GetSpellType() const override;                                         // 53 - { return data.spellType; }
		void                     SetCastingType(MagicSystem::CastingType a_type) override;              // 54 - { data.castingType = a_type; }
		MagicSystem::CastingType GetCastingType() const override;                                       // 55 - { return data.castingType; }
		void                     SetDelivery(MagicSystem::Delivery a_type) override;                    // 56 - { if (Unk_58()) { data.delivery = a_type; } }
		MagicSystem::Delivery    GetDelivery() const override;                                          // 57 - { return data.delivery; }
		float                    GetFixedCastDuration() const override;                                 // 59 - { return (GetCastingType() == MagicSystem::CastingType::kConcentration) ? data.castDuration : 0.0; }
		float                    GetRange() const override;                                             // 5A - { return data.range; }
		bool                     IgnoresResistance() const override;                                    // 5B - { return (GetData()->flags >> 20) & 1; }
		bool                     IgnoreLOS() const override;                                            // 5C - { return (GetData()->flags >> 19) & 1; }
		bool                     GetNoAbsorb() const override;                                          // 5E - { return (GetData()->flags >> 21) & 1; }
		bool                     GetNoDualCastModifications() const override;                           // 5F - { return (GetData()->flags >> 23) & 1; }
		bool                     GetSkillUsageData(SkillUsageData& a_data) const override;              // 60
		void                     AdjustCost(float& a_cost, Actor* a_actor) const override;              // 63
		float                    GetChargeTime() const override;                                        // 64
		ActorValue               GetAssociatedSkill() const override;                                   // 66
		bool                     IsTwoHanded() const override;                                          // 67 - { BGSEquipSlot* equipSlot = BGSEquipType::GetEquipSlot(); return equipSlot && equipSlot->flags & 1; }
		std::uint32_t            GetChunkID() override;                                                 // 68 - { return 'SPIT'; }
		void                     CopyMagicItemData(MagicItem* a_src) override;                          // 69
		void                     LoadMagicItemChunk(TESFile* a_mod, std::uint32_t a_chunkID) override;  // 6A
		void                     LoadChunkDataPostProcess(TESFile* a_mod) override;                     // 6B
		const MagicItem::Data*   GetData1() const override;                                             // 6C - { return &data; }
		MagicItem::Data*         GetData2() override;                                                   // 6D - { return &data; }
		std::uint32_t            GetDataSize() const override;                                          // 6E - { return 0x28; }
		void                     InitFromChunk(TESFile* a_mod) override;                                // 6F
		void                     InitChunk() override;                                                  // 70

		// override (BGSMenuDisplayObject)
		[[nodiscard]] TESBoundObject* GetMenuDisplayObject() const override;  // 04 - { return menuDispObject; }

		// members
		Data data;  // C0 - SPIT
	};
	static_assert(sizeof(SpellItem) == 0xE8);
}
