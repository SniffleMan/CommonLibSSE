#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class ExtraHasNoRumors : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraHasNoRumors;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kHasNoRumors;

		~ExtraHasNoRumors() override;  // 00

		// override (BSExtraData)
		[[nodiscard]] ExtraDataType GetType() const override;  // 01 - { return kHasNoRumors; }

		// members
		bool          noRumors;  // 10
		std::uint8_t  pad11;     // 11
		std::uint16_t pad12;     // 12
		std::uint32_t pad14;     // 14
	};
	static_assert(sizeof(ExtraHasNoRumors) == 0x18);
}
