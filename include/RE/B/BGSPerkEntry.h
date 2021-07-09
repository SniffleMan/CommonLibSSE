#pragma once

#include "RE/B/BGSEntryPoint.h"
#include "RE/F/FormTypes.h"

namespace RE
{
	class Actor;
	class BGSEntryPointFunctionData;
	class TESFile;

	enum class PERK_ENTRY_TYPE
	{
		kQuest = 0,
		kAbility = 1,
		kEntryPoint = 2
	};

	class BGSPerkEntry
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSPerkEntry;

		using EntryPoint = BGSEntryPoint::ENTRY_POINT;

		struct Header  // PRKE
		{
		public:
			// members
			std::uint8_t  rank;      // 0
			std::uint8_t  priority;  // 1
			std::uint16_t unk2;      // 2
			std::uint32_t unk4;      // 4
		};
		static_assert(sizeof(Header) == 0x8);

		virtual bool       CheckConditionFilters(std::uint32_t a_numArgs, void* a_args);  // 00 - { return false; }
		virtual EntryPoint GetFunction();                                                 // 01 - { return 0; }
		[[nodiscard]] virtual void*      GetFunctionData() const;                                       // 02 - { return 0; }

		virtual ~BGSPerkEntry();  // 03

		[[nodiscard]] virtual PERK_ENTRY_TYPE GetType() const = 0;                  // 04
		virtual void            ClearData();                          // 05 - { return; }
		virtual void            InitItem(TESFile* a_owner);           // 06 - { return; }
		virtual bool            Load(TESFile* a_file);                // 07 - { return true; }
		virtual void            SetParent(BGSPerk* a_parent);         // 08 - { return; }
		[[nodiscard]] virtual std::uint16_t   GetID() const;                        // 09 - { return 0xFFFF; }
		virtual void            ApplyPerkEntry(Actor* a_actor) = 0;   // 0A
		virtual void            RemovePerkEntry(Actor* a_actor) = 0;  // 0B

		[[nodiscard]] std::uint8_t GetRank() const;
		[[nodiscard]] std::uint8_t GetPriority() const;

		// members
		Header header;  // 08 - PRKE
	};
	static_assert(sizeof(BGSPerkEntry) == 0x10);
}
