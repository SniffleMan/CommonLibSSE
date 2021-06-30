#pragma once

#include "RE/B/BSString.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTHashMap.h"
#include "RE/B/BSTList.h"
#include "RE/F/FormTypes.h"
#include "RE/N/NiPoint2.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/N/NiTPointerMap.h"
#include "RE/T/TESForm.h"
#include "RE/T/TESFullName.h"
#include "RE/T/TESModel.h"
#include "RE/T/TESTexture.h"

namespace RE
{
	class BGSTerrainManager;

	struct WORLD_MAP_DATA  // MNAM
	{
	public:
		struct CameraData
		{
			float minHeight;     // 0
			float maxHeight;     // 4
			float initialPitch;  // 8
		};
		static_assert(sizeof(CameraData) == 0xC);

		// members
		std::uint32_t usableWidth;   // 00
		std::uint32_t usableHeight;  // 04
		std::int16_t  nwCellX;       // 08
		std::int16_t  nwCellY;       // 0A
		std::int16_t  seCellX;       // 0C
		std::int16_t  seCellY;       // 0E
		CameraData    cameraData;    // 10
	};
	static_assert(sizeof(WORLD_MAP_DATA) == 0x1C);

	struct WORLD_MAP_OFFSET_DATA  // ONAM
	{
	public:
		// members
		float mapScale;    // 00
		float mapOffsetX;  // 04
		float mapOffsetY;  // 08
		float mapOffsetZ;  // 0C
	};
	static_assert(sizeof(WORLD_MAP_OFFSET_DATA) == 0x10);

	struct CellID
	{
	public:
		constexpr CellID() noexcept :
			CellID(0, 0)
		{}

		constexpr CellID(std::int16_t a_y, std::int16_t a_x) noexcept :
			y(a_y),
			x(a_x)
		{}

		[[nodiscard]] friend constexpr bool operator==(const CellID& a_lhs, const CellID& a_rhs) noexcept
		{
			return a_lhs[0] == a_rhs[0] && a_lhs[1] == a_rhs[1];
		}

		[[nodiscard]] constexpr std::int16_t& operator[](std::size_t a_idx) noexcept
		{
			assert(a_idx < 2);
			return std::addressof(y)[a_idx];
		}

		[[nodiscard]] constexpr const std::int16_t& operator[](std::size_t a_idx) const noexcept
		{
			assert(a_idx < 2);
			return std::addressof(y)[a_idx];
		}

		// members
		std::int16_t y;
		std::int16_t x;
	};
	static_assert(sizeof(CellID) == 0x4);

	template <>
	struct BSCRC32_<CellID>
	{
	public:
		[[nodiscard]] inline std::uint32_t operator()(CellID a_key) const noexcept
		{
			return BSCRC32_<std::uint32_t>()(reinterpret_cast<const std::uint32_t&>(a_key));
		}
	};

	class BGSLargeRefData  // RNAM
	{
	public:
		// RNAM format in plugins is cell x,y -> formID + cell that contains refr x,y
		// a lot of RNAM data is for refrs that are actually in adjacent cells, it is currently unknown what behavior this has in game
		BSTHashMap<CellID, FormID*> cellFormIDMap;  // 00 - full data merged at runtime, value is an array of FormIDs with array size as the first entry
		BSTHashMap<FormID, CellID>  formIDCellMap;  // 30 - maps FormID to cell so opposite of above map

		// this filtered version of the full data removes all duplicate RNAM entries and also all entries where cell x,y doesn't match cell that contains refr x,y
		// this is the one actually used for loading large references on cell attach
		BSTHashMap<CellID, FormID*> cellFormIDMapFiltered;  // 60
	};
	static_assert(sizeof(BGSLargeRefData) == 0x90);

	class TESWorldSpace :
		public TESForm,      // 000
		public TESFullName,  // 020
		public TESModel      // 030
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESWorldSpace;
		inline static constexpr auto FORMTYPE = FormType::WorldSpace;

		enum class Flag
		{
			kNone = 0,
			kSmallWorld = 1 << 0,
			kCantFastTravel = 1 << 1,
			kNoLODWater = 1 << 3,
			kNoLandscape = 1 << 4,
			kNoSky = 1 << 5,
			kFixedDimensions = 1 << 6,
			kNoGrass = 1 << 7,
		};

		enum class ParentUseFlag
		{
			kNone = 0,
			kUseLandData = 1 << 0,
			kUseLODData = 1 << 1,
			kDontUseMapData = 1 << 2,
			kUseWaterData = 1 << 3,
			kUseClimateData = 1 << 4,
			kUseImageSpaceData = 1 << 5,  // unused
			kUseSkyCell = 1 << 6,
		};

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12,
				kCantWait = 1 << 19
			};
		};

		struct ShortPoint
		{
		public:
			// members
			std::int16_t x;
			std::int16_t y;
		};
		static_assert(sizeof(ShortPoint) == 0x4);

		~TESWorldSpace() override;  // 00

		// override (TESForm)
		void        InitializeData() override;                                          // 04
		void        ClearData() override;                                               // 05
		bool        Load(TESFile* a_mod) override;                                      // 06
		bool        LoadPartial(TESFile* a_mod) override;                               // 07
		TESForm*    CreateDuplicateForm(bool a_createEditorID, void* a_arg2) override;  // 09
		bool        FindInFileFast(TESFile* a_mod) override;                            // 0C
		void        InitItemImpl() override;                                            // 13
		const char* GetFormEditorID() const override;                                   // 32 - { return editorID.c_str(); }
		bool        SetFormEditorID(const char* a_str) override;                        // 33 - { editorID = a_str; }
		bool        IsParentForm() override;                                            // 34 - { return true; }
		bool        IsFormTypeChild(FormType a_type) override;                          // 36

		[[nodiscard]] bool HasMaxHeightData() const;

		// members
		BSTHashMap<CellID, TESObjectCELL*>                            cellMap;                  // 058
		TESObjectCELL*                                                persistentCell;           // 088
		BGSTerrainManager*                                            terrainManager;           // 090
		TESClimate*                                                   climate;                  // 098 - CNAM
		stl::enumeration<Flag, std::uint8_t>                          flags;                    // 0A0 - DATA
		std::uint8_t                                                  unk0A1;                   // 0A1 - more flags
		stl::enumeration<ParentUseFlag, std::uint16_t>                parentUseFlags;           // 0A2 - PNAM
		ShortPoint                                                    fixedCenter;              // 0A4 - WCTR
		BSTHashMap<std::uint32_t, BSTArray<NiPointer<TESObjectREFR>>> fixedPersistentRefMap;    // 0A8
		BSTArray<NiPointer<TESObjectREFR>>                            mobilePersistentRefs;     // 0D8
		NiTPointerMap<std::uint32_t, BSSimpleList<TESObjectREFR*>*>*  overlappedMultiboundMap;  // 0F0
		TESObjectCELL*                                                skyCell;                  // 0F8
		BSTHashMap<FormID, BGSLocation*>                              locationMap;              // 100
		void*                                                         unk130;                   // 130 - smart ptr
		void*                                                         unk138;                   // 138
		void*                                                         unk140;                   // 140
		void*                                                         unk148;                   // 148 - smart ptr
		void*                                                         unk150;                   // 150 - smart ptr
		TESWorldSpace*                                                parentWorld;              // 158 - WNAM
		BGSLightingTemplate*                                          lightingTemplate;         // 160 - LTMP
		TESWaterForm*                                                 worldWater;               // 168 - NAM2
		TESWaterForm*                                                 lodWater;                 // 170 - NAM3
		float                                                         lodWaterHeight;           // 178 - NAM4
		std::uint32_t                                                 pad17C;                   // 17C
		std::uint64_t                                                 unk180;                   // 180
		WORLD_MAP_DATA                                                worldMapData;             // 188 - MNAM
		WORLD_MAP_OFFSET_DATA                                         worldMapOffsetData;       // 1A4 - ONAM
		std::uint32_t                                                 pad1B4;                   // 1B4
		BGSMusicType*                                                 musicType;                // 1B8 - ZNAM
		NiPoint2                                                      minimumCoords;            // 1C0
		NiPoint2                                                      maximumCoords;            // 1C8
		BSTHashMap<UnkKey, UnkValue>                                  unk1D0;                   // 1D0 - BSTHashMap<TESFile*, OFFSET_DATA*> offsetDataMap?
		BSString                                                      editorID;                 // 200 - EDID
		float                                                         defaultLandHeight;        // 210 - DNAM~
		float                                                         defaultWaterHeight;       // 214 - ~DNAM
		float                                                         distantLODMult;           // 218 - NAMA
		std::uint32_t                                                 pad21C;                   // 21C
		BGSEncounterZone*                                             encounterZone;            // 220 - XEZN
		BGSLocation*                                                  location;                 // 228 - XLCN
		TESTexture                                                    canopyShadowTexture;      // 230 - TNAM
		TESTexture                                                    waterEnvMap;              // 240 - UNAM
		BGSLargeRefData                                               largeRefData;             // 250 - RNAM
		std::uint64_t                                                 unk2E0;                   // 2E0
		BSTHashMap<UnkKey, UnkValue>                                  unk2E8;                   // 2E8
		BSTHashMap<UnkKey, UnkValue>                                  unk318;                   // 318
		float                                                         northRotation;            // 348
		std::uint32_t                                                 pad34C;                   // 34C
		std::int8_t*                                                  maxHeightData;            // 350 - MHDT
	};
	static_assert(sizeof(TESWorldSpace) == 0x358);
}
