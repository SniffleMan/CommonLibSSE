#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class ExtraDetachTime : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraDetachTime;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kDetachTime;

		~ExtraDetachTime() override;  // 00

		// override (BSExtraData)
		[[nodiscard]] ExtraDataType GetType() const override;  // 01 - { return kDetachTime; }

		// members
		std::uint32_t time;   // 10
		std::uint32_t pad14;  // 14
	};
	static_assert(sizeof(ExtraDetachTime) == 0x18);
}
