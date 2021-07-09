#pragma once

#include "RE/A/AITimeStamp.h"
#include "RE/B/BSExtraData.h"
#include "RE/B/BSTArray.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class ExtraFriendHits : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraFriendHits;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kFriendHits;

		~ExtraFriendHits() override;  // 00

		// override (BSExtraData)
		[[nodiscard]] ExtraDataType GetType() const override;  // 01 - { return kFriendHits; }

		// members
		BSTArray<AITimeStamp> hits;  // 10
	};
	static_assert(sizeof(ExtraFriendHits) == 0x28);
}
