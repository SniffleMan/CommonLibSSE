#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class BSAnimationGraphManager;

	class ExtraAnimGraphManager : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraAnimGraphManager;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kAnimGraphManager;

		~ExtraAnimGraphManager() override;  // 00

		// override (BSExtraData)
		[[nodiscard]] ExtraDataType GetType() const override;  // 01 - { return kAnimGraphManager; }

		// members
		BSTSmartPointer<BSAnimationGraphManager> animGraphMgr;  // 10
	};
	static_assert(sizeof(ExtraAnimGraphManager) == 0x18);
}
