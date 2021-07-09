#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/B/BSFixedString.h"
#include "RE/B/BSTArray.h"
#include "RE/E/ExtraDataTypes.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class AddCellGrassTask;
	class BSInstanceTriShape;

	struct CellGrassData
	{
		std::uint64_t                 grassTypeKey;   // 00
		BSFixedString                 grassModelKey;  // 08
		NiPointer<BSInstanceTriShape> triShape;       // 10
		BSTArray<void*>               unk18;          // 18
		BSTArray<void*>               unk30;          // 30
	};
	static_assert(sizeof(CellGrassData) == 0x48);

	class ExtraCellGrassData : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraCellGrassData;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kCellGrassData;

		~ExtraCellGrassData() override;  // 00

		// override (BSExtraData)
		[[nodiscard]] ExtraDataType GetType() const override;  // 01 - { return kCellGrassData; }

		// members
		BSTArray<CellGrassData*>    grassHandles;  // 10
		NiPointer<AddCellGrassTask> addGrassTask;  // 28
	};
	static_assert(sizeof(ExtraCellGrassData) == 0x30);
}
