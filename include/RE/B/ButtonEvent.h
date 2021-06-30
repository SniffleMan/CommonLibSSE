#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/I/IDEvent.h"
#include "RE/I/InputEvent.h"

namespace RE
{
	class ButtonEvent : public IDEvent
	{
	public:
		inline static constexpr auto RTTI = RTTI_ButtonEvent;

		~ButtonEvent() override;  // 00

		[[nodiscard]] constexpr float Value() const noexcept { return value; }
		[[nodiscard]] constexpr float HeldDuration() const noexcept { return heldDownSecs; }
		[[nodiscard]] constexpr bool  IsPressed() const noexcept { return Value() > 0.0F; }
		[[nodiscard]] constexpr bool  IsRepeating() const noexcept { return HeldDuration() > 0.0F; }
		[[nodiscard]] constexpr bool  IsDown() const noexcept { return IsPressed() && (HeldDuration() == 0.0F); }
		[[nodiscard]] constexpr bool  IsHeld() const noexcept { return IsPressed() && IsRepeating(); }
		[[nodiscard]] constexpr bool  IsUp() const noexcept { return (Value() == 0.0F) && IsRepeating(); }

		// members
		float value;         // 28
		float heldDownSecs;  // 2C
	};
	static_assert(sizeof(ButtonEvent) == 0x30);
}
