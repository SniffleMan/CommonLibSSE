#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSTArray.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class ExtraFollower : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraFollower;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kFollower;

		struct FollowerInfo
		{
			ActorHandle actor;                   // 0
			float       intendedFollowDistance;  // 4
		};
		static_assert(sizeof(FollowerInfo) == 0x8);

		~ExtraFollower() override;  // 00

		// override (BSExtraData)
		[[nodiscard]] ExtraDataType GetType() const override;  // 01 - { return kFollower; }

		// members
		BSTArray<FollowerInfo> actorFollowers;  // 10
	};
	static_assert(sizeof(ExtraFollower) == 0x28);
}
