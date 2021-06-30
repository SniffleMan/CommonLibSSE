#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class ExtraIgnoredBySandbox : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraIgnoredBySandbox;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kIgnoredBySandbox;

		~ExtraIgnoredBySandbox() override;  // 00

		// override (BSExtraData)
		[[nodiscard]] ExtraDataType GetType() const override;  // 01 - { return kIgnoredBySandbox; }
	};
	static_assert(sizeof(ExtraIgnoredBySandbox) == 0x10);
}
