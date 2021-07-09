#pragma once

#include "RE/N/NiPoint3.h"

namespace RE
{
	class NiAVObject;

	struct BSSoundHandle
	{
	public:
		enum : std::uint32_t
		{
			kInvalidID = static_cast<std::uint32_t>(-1)
		};

		enum class AssumedState
		{
			kInitialized = 0,
			kPlaying = 1,
			kStopped = 2,
			kPaused = 3
		};

		enum class LoopType
		{
			kNone = 0,
			kWholeFile = 1,
			kEnvFast = 2,
			kEnvSlow = 3
		};

		BSSoundHandle();
		~BSSoundHandle() = default;

		[[nodiscard]] bool IsValid() const;
		bool SetPosition(NiPoint3 a_pos);
		void SetObjectToFollow(NiAVObject* a_node);
		bool Stop();
		bool Play();

		// members
		std::uint32_t                                 soundID;        // 00
		bool                                          assumeSuccess;  // 04
		std::uint8_t                                  pad05;          // 05
		std::uint16_t                                 pad06;          // 06
		stl::enumeration<AssumedState, std::uint32_t> state;          // 08
	};
	static_assert(sizeof(BSSoundHandle) == 0xC);
}
