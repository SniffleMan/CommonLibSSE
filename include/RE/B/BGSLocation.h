#pragma once

#include "RE/B/BGSKeywordForm.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTHashMap.h"
#include "RE/B/BSTTuple.h"
#include "RE/F/FormTypes.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/T/TESForm.h"
#include "RE/T/TESFullName.h"

namespace RE
{
	class QueuedPromoteLocationReferencesTask;

	struct UnloadedRefData
	{
	public:
		union CellKey
		{
			BSTTuple<std::int16_t, std::int16_t> xy;
			std::uint32_t                        raw;
		};
		static_assert(sizeof(CellKey) == 0x4);

		// members
		FormID  refID;          // 0
		FormID  parentSpaceID;  // 4
		CellKey cellKey;        // 8
	};
	static_assert(sizeof(UnloadedRefData) == 0xC);

	struct SpecialRefData  // LCSR
	{
	public:
		// members
		BGSLocationRefType* type;     // 00
		UnloadedRefData     refData;  // 08
		std::uint32_t       pad14;    // 14
	};
	static_assert(sizeof(SpecialRefData) == 0x18);

	struct UniqueNPCData  // LCUN
	{
	public:
		// members
		Actor*        actor;      // 00
		FormID        refID;      // 08
		std::uint32_t pad0C;      // 0C
		BGSLocation*  editorLoc;  // 10
	};
	static_assert(sizeof(UniqueNPCData) == 0x18);

	struct OverrideData
	{
	public:
		// members
		BSTArray<UnloadedRefData> addedData;    // 00 - ACPR
		BSTSet<FormID>            removedData;  // 18 - RCPR
	};
	static_assert(sizeof(OverrideData) == 0x48);

	class BGSLocation :
		public TESForm,        // 00
		public TESFullName,    // 20
		public BGSKeywordForm  // 30
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSLocation;
		inline static constexpr auto FORMTYPE = FormType::Location;

		struct ChangeFlags
		{
			enum ChangeFlag : std::uint32_t
			{
				kKeywordData = 1 << 30,
				kCleared = (std::uint32_t)1 << 31
			};
		};

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12,
				kCleared = (std::uint32_t)1 << 31
			};
		};

		struct KEYWORD_DATA
		{
		public:
			// members
			BGSKeyword*   keyword;  // 00
			float         data;     // 08
			std::uint32_t pad0C;    // 0C
		};
		static_assert(sizeof(KEYWORD_DATA) == 0x10);

		~BGSLocation() override;  // 00

		// override (TESForm)
		void InitializeData() override;                    // 04
		bool Load(TESFile* a_mod) override;                // 06
		bool FindInFileFast(TESFile* a_mod) override;      // 0C
		void SaveGame(BGSSaveFormBuffer* a_buf) override;  // 0E
		void LoadGame(BGSLoadFormBuffer* a_buf) override;  // 0F
		void Revert(BGSLoadFormBuffer* a_buf) override;    // 12
		void InitItemImpl() override;                      // 13

		[[nodiscard]] bool IsCleared() const;
		bool IsChild(const BGSLocation* a_possibleChild) const;
		bool IsParent(const BGSLocation* a_possibleParent) const;
		[[nodiscard]] bool IsLoaded() const;

		// members
		BGSLocation*                                   parentLoc;               // 48 - PNAM
		TESFaction*                                    unreportedCrimeFaction;  // 50 - FNAM
		BGSMusicType*                                  musicType;               // 58 - NAM1
		ObjectRefHandle                                worldLocMarker;          // 60 - MNAM
		float                                          worldLocRadius;          // 64 - RNAM
		ObjectRefHandle                                horseLocMarker;          // 68 - NAM0
		std::uint32_t                                  pad6C;                   // 6C
		BSTArray<SpecialRefData>                       specialRefs;             // 70 - LCSR
		BSTArray<UniqueNPCData>                        uniqueNPCs;              // 88 - LCUN
		OverrideData*                                  overrideData;            // A0
		NiPointer<QueuedPromoteLocationReferencesTask> promoteRefsTask;         // A8
		BSTArray<ObjectRefHandle>                      promotedRefs;            // B0
		volatile std::int32_t                          loadedCount;             // C8
		std::uint32_t                                  fileOffset;              // CC
		BSTArray<KEYWORD_DATA>                         keywordData;             // D0
		std::uint32_t                                  lastChecked;             // E8
		bool                                           cleared;                 // EC
		bool                                           everCleared;             // ED
		std::uint16_t                                  padEE;                   // EE
	};
	static_assert(sizeof(BGSLocation) == 0xF0);
}
