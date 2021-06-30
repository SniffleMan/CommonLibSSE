#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class NiNode;

	class ExtraCell3D : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraCell3D;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kCell3D;

		~ExtraCell3D() override;  // 00

		// override (BSExtraData)
		[[nodiscard]] ExtraDataType GetType() const override;  // 01 - { return kCell3D; }

		// members
		NiPointer<NiNode> cellNode;  // 10
	};
	static_assert(sizeof(ExtraCell3D) == 0x18);
}
