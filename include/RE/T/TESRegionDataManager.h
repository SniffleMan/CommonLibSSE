#pragma once

namespace RE
{
	enum class REGION_DATA_ID;

	class TESFile;
	class TESRegion;
	class TESRegionData;
	class TESRegionDataGrass;
	class TESRegionDataLandscape;
	class TESRegionDataMap;
	class TESRegionDataObjects;
	class TESRegionDataSound;
	class TESRegionDataWeather;

	class TESRegionDataManager
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESRegionDataManager;

		virtual ~TESRegionDataManager();  // 00

		// add
		virtual TESRegion*              GetLastLoadedRegion();                                 // 01 - { return lastLoadedRegion; }
		[[nodiscard]] virtual TESRegionData*          ConstructRegionData(REGION_DATA_ID a_id) const;        // 02
		virtual TESRegionDataObjects*   AsRegionDataObjects(TESRegionData* a_data) const;      // 03
		virtual TESRegionDataWeather*   AsRegionDataWeather(TESRegionData* a_data) const;      // 04
		virtual TESRegionDataMap*       AsRegionDataMap(TESRegionData* a_data) const;          // 05
		virtual TESRegionDataLandscape* AsRegionDataLandscape(TESRegionData* a_data) const;    // 06
		virtual TESRegionDataGrass*     AsRegionDataGrass(TESRegionData* a_data) const;        // 07
		virtual TESRegionDataSound*     AsRegionDataSound(TESRegionData* a_data) const;        // 08
		virtual bool                    LoadRegionData(TESFile* a_file, TESRegion* a_region);  // 09

		// members
		TESRegion* lastLoadedRegion;  // 08
	};
	static_assert(sizeof(TESRegionDataManager) == 0x10);
}
