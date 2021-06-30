#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class BSPortal;

	class ExtraPortal : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraPortal;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kPortal;

		~ExtraPortal() override;  // 00

		// override (BSExtraData)
		[[nodiscard]] ExtraDataType GetType() const override;  // 01 - { return kPortal; }

		// members
		NiPointer<BSPortal> portal;  // 10
	};
	static_assert(sizeof(ExtraPortal) == 0x18);
}
