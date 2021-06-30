#pragma once

#include "RE/F/FormTypes.h"

namespace RE
{
	class TESFile;

	class BGSEntryPointFunctionData
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSEntryPointFunctionData;

		enum class FunctionType
		{
			kInvalid = 0,
			kOneValue = 1,
			kTwoValue = 2,
			kLeveledList = 3,
			kActivateChoice = 4,
			kSpellItem = 5,
			kBooleanGraphVariable = 6,
			kText = 7
		};

		virtual ~BGSEntryPointFunctionData();  // 00

		[[nodiscard]] virtual FunctionType GetType() const = 0;                   // 01
		virtual bool         LoadFunctionData(TESFile* a_mod) = 0;  // 02
		virtual void         ResolveForms(TESFile* a_mod);          // 03 - { return; }
		virtual void         Unk_04(void);                          // 04 - { return; }
		virtual void         Unk_05(void);                          // 05 - { return 0xFFFF; }
		virtual void         SetPerk(BGSPerk* a_perk);              // 06 - { return; }
		virtual BGSPerk*     GetPerk();                             // 07 - { return 0; }
	};
	static_assert(sizeof(BGSEntryPointFunctionData) == 0x8);
}
