#pragma once

#include "RE/F/FormTypes.h"
#include "RE/T/TESBoundAnimObject.h"
#include "RE/T/TESLeveledList.h"
#include "RE/T/TESModelTextureSwap.h"

namespace RE
{
	class TESLevCharacter :
		public TESBoundAnimObject,  // 00
		public TESLeveledList,      // 30
		public TESModelTextureSwap  // 58
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESLevCharacter;
		inline static constexpr auto FORMTYPE = FormType::LeveledNPC;

		struct ChangeFlags
		{
			enum ChangeFlag : std::uint32_t
			{
				kAddedObject = (std::uint32_t)1 << 31
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

		~TESLevCharacter() override;  // 00

		// override (TESBoundAnimObject)
		bool        Load(TESFile* a_mod) override;                // 06
		void        SaveGame(BGSSaveFormBuffer* a_buf) override;  // 0E
		void        LoadGame(BGSLoadFormBuffer* a_buf) override;  // 0F
		void        Revert(BGSLoadFormBuffer* a_buf) override;    // 12
		void        InitItemImpl() override;                      // 13
		void        UnClone3D(TESObjectREFR* a_ref) override;     // 4A - { return; }
		NiAVObject* Clone3D(TESObjectREFR* a_ref) override;       // 4A - { return 0; }

		// override (TESLeveledList)
		std::int32_t GetLevDifferenceMax() override;                            // 06 - { return iLevCharLevelDifferenceMax; }
		[[nodiscard]] bool         GetCanContainFormsOfType(FormType a_type) const override;  // 07 - { return a_type <= FormType::LeveledCharacter; }
	};
	static_assert(sizeof(TESLevCharacter) == 0x90);
}
