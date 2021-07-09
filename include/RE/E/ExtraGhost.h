#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class ExtraGhost : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraGhost;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kGhost;

		~ExtraGhost() override;  // 00

		// override (BSExtraData)
		[[nodiscard]] ExtraDataType GetType() const override;  // 01 - { return kGhost; }

		// members
		bool          ghost;  // 10
		std::uint8_t  pad11;  // 11
		std::uint16_t pad12;  // 12
		std::uint32_t pad14;  // 14
	};
	static_assert(sizeof(ExtraGhost) == 0x18);
}
