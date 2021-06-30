#pragma once

#include "RE/B/BSTList.h"
#include "RE/T/TESRegionData.h"

namespace RE
{
	struct WeatherType;

	class TESRegionDataWeather : public TESRegionData
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESRegionDataWeather;
		inline static constexpr auto TYPE = Type::kWeather;

		~TESRegionDataWeather() override;  // 00

		// override (TESRegionData)
		Type GetType() const override;                              // 03 - { return Type::kWeather; }
		void ConstructSelf() override;                              // 04
		void Unk_05(void) override;                                 // 05
		void CopyFrom(TESRegionData* a_src, bool a_copy) override;  // 06
		[[nodiscard]] bool IsLoaded() const override;                             // 07 - { return weatherTypes.next || weatherTypes.cur; }

		// add
		virtual void Unk_08(void);  // 08

		// members
		BSSimpleList<WeatherType*> weatherTypes;  // 10
	};
	static_assert(sizeof(TESRegionDataWeather) == 0x20);
}
