#pragma once

#include "RE/G/GFxState.h"

namespace RE
{
	class GFxActionControl : public GFxState
	{
	public:
		enum class ActionControlFlags
		{
			kNone = 0,
			kVerbose = 1 << 0,
			kSuppressErrors = 1 << 1,
			kLogRootFilenames = 1 << 2,   // Display filename for root movie
			kLogChildFilenames = 1 << 3,  // Display filename for child movie
			kLongFilenames = 1 << 4       // Display full path
		};

		inline GFxActionControl(ActionControlFlags a_actionFlags = ActionControlFlags::kLogChildFilenames) :
			GFxState(StateType::kActionControl),
			actionFlags(a_actionFlags),
			pad1C(0)
		{}

		[[nodiscard]] constexpr ActionControlFlags GetFlags() const { return *actionFlags; }
		constexpr void               SetFlags(ActionControlFlags a_actionFlags) { actionFlags = a_actionFlags; }

		constexpr void SetVerboseLogging() noexcept { actionFlags.set(ActionControlFlags::kVerbose); }
		constexpr void UnsetVerboseLogging() noexcept { actionFlags.reset(ActionControlFlags::kVerbose); }

		constexpr void SetErrorSuppression() noexcept { actionFlags.set(ActionControlFlags::kSuppressErrors); }
		constexpr void UnsetErrorSuppression() noexcept { actionFlags.reset(ActionControlFlags::kSuppressErrors); }

		constexpr void SetRootFilenameLogging() noexcept { actionFlags.set(ActionControlFlags::kLogRootFilenames); }
		constexpr void UnsetRootFilenameLogging() noexcept { actionFlags.reset(ActionControlFlags::kLogRootFilenames); }

		constexpr void SetChildFilenameLogging() noexcept { actionFlags.set(ActionControlFlags::kLogChildFilenames); }
		constexpr void UnsetChildFilenameLogging() noexcept { actionFlags.reset(ActionControlFlags::kLogChildFilenames); }

		constexpr void SetAllFilenameLogging() noexcept { actionFlags.set(ActionControlFlags::kLogRootFilenames, ActionControlFlags::kLogChildFilenames); }
		constexpr void UnsetAllFilenameLogging() noexcept { actionFlags.reset(ActionControlFlags::kLogRootFilenames, ActionControlFlags::kLogChildFilenames); }

		constexpr void SetLongFilenameLogging() noexcept { actionFlags.set(ActionControlFlags::kLongFilenames); }
		constexpr void UnsetLongFilenameLogging() noexcept { actionFlags.reset(ActionControlFlags::kLongFilenames); }

		// members
		stl::enumeration<ActionControlFlags, std::uint32_t> actionFlags;  // 18
		std::uint32_t                                       pad1C;        // 1C
	};
	static_assert(sizeof(GFxActionControl) == 0x20);
}
