#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class BSMultiBoundRoom;

	class ExtraRoom : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraRoom;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kRoom;

		~ExtraRoom() override;  // 00

		// override (BSExtraData)
		[[nodiscard]] ExtraDataType GetType() const override;  // 01 - { return kRoom; }

		// members
		NiPointer<BSMultiBoundRoom> room;  // 10
	};
	static_assert(sizeof(ExtraRoom) == 0x18);
}
