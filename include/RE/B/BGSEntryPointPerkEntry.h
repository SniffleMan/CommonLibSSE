#pragma once

#include "RE/B/BGSPerkEntry.h"
#include "RE/F/FormTypes.h"
#include "RE/M/MemoryManager.h"

namespace RE
{
	class BGSEntryPointFunctionData;
	class TESCondition;

	class BGSEntryPointPerkEntry : public BGSPerkEntry
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSEntryPointPerkEntry;

		struct EntryData  // DATA
		{
		public:
			enum class Function
			{
				kSetValue = 1,
				kAddValue = 2,
				kMultiplyValue = 3,
				kAddRangeToValue = 4,
				kAddActorValueMult = 5,
				kAbsoluteValue = 6,
				kNegativeAbsoluteValue = 7,
				kAddLeveledList = 8,
				kAddActivateChoice = 9,
				kSelectSpell = 10,
				kSelectText = 11,
				kSetToActorValueMult = 12,
				kMultiplyActorValueMult = 13,
				kMultiply1PlusActorValueMult = 14,
				kSetText = 15
			};

			// members
			stl::enumeration<EntryPoint, std::uint8_t> entryPoint;  // 0
			stl::enumeration<Function, std::uint8_t>   function;    // 1
			std::uint8_t                               numArgs;     // 2
			std::uint8_t                               unk3;        // 3
			std::uint32_t                              unk4;        // 4
		};
		static_assert(sizeof(EntryData) == 0x8);

		// override (BGSPerkEntry)
		bool       CheckConditionFilters(std::uint32_t a_numArgs, void* a_args) override;  // 00
		EntryPoint GetFunction() override;                                                 // 01 - { return function; }
		void*      GetFunctionData() const override;                                       // 02 - { return functionData; }

		~BGSEntryPointPerkEntry() override;  // 03

		PERK_ENTRY_TYPE GetType() const override;                  // 04 - { return kEntryPoint; }
		void            ClearData() override;                      // 05
		void            InitItem(TESFile* a_owner) override;       // 06
		bool            Load(TESFile* a_file) override;            // 07
		void            SetParent(BGSPerk* a_parent) override;     // 08
		std::uint16_t   GetID() const override;                    // 09
		void            ApplyPerkEntry(Actor* a_actor) override;   // 0A
		void            RemovePerkEntry(Actor* a_actor) override;  // 0B

		[[nodiscard]] bool IsEntryPoint(EntryPoint a_entryPoint) const;

		// members
		EntryData                  entryData;     // 10 - DATA
		BGSEntryPointFunctionData* functionData;  // 18
		SimpleArray<TESCondition>  conditions;    // 20
		BGSPerk*                   perk;          // 28
	};
	static_assert(sizeof(BGSEntryPointPerkEntry) == 0x30);
}
