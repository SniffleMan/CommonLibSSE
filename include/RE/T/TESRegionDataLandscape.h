#pragma once

#include "RE/B/BSString.h"
#include "RE/T/TESRegionData.h"

namespace RE
{
	class TESFile;
	class TESTexture;

	class TESRegionDataLandscape : public TESRegionData
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESRegionDataLandscape;
		inline static constexpr auto TYPE = Type::kLand;

		~TESRegionDataLandscape() override;  // 00

		// override (TESRegionData)
		Type GetType() const override;                              // 03 - { return Type::kLand; }
		void ConstructSelf() override;                              // 04
		void Unk_05(void) override;                                 // 05
		void CopyFrom(TESRegionData* a_src, bool a_copy) override;  // 06
		[[nodiscard]] bool IsLoaded() const override;                             // 07

		// add
		virtual bool LoadIcon(TESFile* a_mod);           // 08
		virtual void GetIconFileName(BSString* a_dst);   // 09
		virtual bool SetIconFileName(BSString* a_name);  // 0A

		// members
		TESTexture* icon;  // 10
	};
	static_assert(sizeof(TESRegionDataLandscape) == 0x18);
}
