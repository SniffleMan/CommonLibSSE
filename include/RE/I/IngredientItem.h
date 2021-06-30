#pragma once

#include "RE/B/BGSDestructibleObjectForm.h"
#include "RE/B/BGSEquipType.h"
#include "RE/B/BGSPickupPutdownSounds.h"
#include "RE/F/FormTypes.h"
#include "RE/M/MagicItem.h"
#include "RE/T/TESIcon.h"
#include "RE/T/TESModelTextureSwap.h"
#include "RE/T/TESValueForm.h"
#include "RE/T/TESWeightForm.h"

namespace RE
{
	class IngredientItem :
		public MagicItem,                  // 000
		public TESModelTextureSwap,        // 090
		public TESIcon,                    // 0C8
		public TESWeightForm,              // 0D8
		public BGSEquipType,               // 0E8
		public BGSDestructibleObjectForm,  // 0F8
		public BGSPickupPutdownSounds,     // 108
		public TESValueForm                // 120
	{
	public:
		inline static constexpr auto RTTI = RTTI_IngredientItem;
		inline static constexpr auto FORMTYPE = FormType::Ingredient;

		enum class IngredientFlag
		{
			kNone = 0,
			kCostOverride = 1 << 0,
			kFoodItem = 1 << 1,
			kExtendDuration = 1 << 3,
			kReferencesPersist = 1 << 8
		};

		struct ChangeFlags
		{
			enum ChangeFlag : std::uint32_t
			{
				kIngredientUse = (std::uint32_t)1 << 31
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

		class Data  // ENIT
		{
		public:
			// members
			std::int32_t                                    costOverride;  // 00
			stl::enumeration<IngredientFlag, std::uint32_t> flags;         // 04
		};
		static_assert(sizeof(Data) == 0x8);

		struct GameData
		{
		public:
			// members
			std::uint16_t knownEffectFlags;
			std::uint16_t playerUses;
		};
		static_assert(sizeof(GameData) == 0x4);

		~IngredientItem() override;  // 00

		// override (MagicItem)
		void                     InitializeData() override;                                             // 04
		void                     ClearData() override;                                                  // 05
		void                     SaveGame(BGSSaveFormBuffer* a_buf) override;                           // 0E
		void                     LoadGame(BGSLoadFormBuffer* a_buf) override;                           // 0F
		void                     Revert(BGSLoadFormBuffer* a_buf) override;                             // 12
		void                     InitItemImpl() override;                                               // 13
		MagicSystem::SpellType   GetSpellType() const override;                                         // 53 - { return MagicSystem::SpellType::kIngredient; }
		MagicSystem::CastingType GetCastingType() const override;                                       // 55 - { return  MagicSystem::CastingType::kFireAndForget; }
		MagicSystem::Delivery    GetDelivery() const override;                                          // 57 - { return MagicSystem::Delivery::kSelf; }
		bool                     IsFood() const override;                                               // 5D - { return (GetData()->flags >> 1) & 1; }
		bool                     GetSkillUsageData(SkillUsageData& a_data) const override;              // 60
		std::uint32_t            GetMaxEffectCount() const override;                                    // 65 - { return 4; }
		ActorValue               GetAssociatedSkill() const override;                                   // 66 - { return ActorValue::kConfidence; }
		std::uint32_t            GetChunkID() override;                                                 // 68 - { return 'ENIT'; }
		void                     CopyMagicItemData(MagicItem* a_src) override;                          // 69
		void                     LoadMagicItemChunk(TESFile* a_mod, std::uint32_t a_chunkID) override;  // 6A
		const MagicItem::Data*   GetData1() const override;                                             // 6C - { return &effectData; }
		MagicItem::Data*         GetData2() override;                                                   // 6D - { return &effectData; }
		std::uint32_t            GetDataSize() const override;                                          // 6E - { return 0x8; }
		void                     InitFromChunk(TESFile* a_mod) override;                                // 6F
		void                     InitChunk() override;                                                  // 70

		// override (BGSKeywordForm)
		[[nodiscard]] BGSKeyword* GetDefaultKeyword() const override;  // 05

		// members
		Data          data;      // 130 - ENIT
		GameData      gamedata;  // 138
		std::uint32_t pad13C;    // 13C
	};
	static_assert(sizeof(IngredientItem) == 0x140);
}
