#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/I/InputDevices.h"

namespace RE
{
	enum class INPUT_EVENT_TYPE
	{
		kButton = 0,
		kMouseMove,
		kChar,
		kThumbstick,
		kDeviceConnect,
		kKinect
	};

	class ButtonEvent;
	class IDEvent;

	class InputEvent
	{
	public:
		inline static constexpr auto RTTI = RTTI_InputEvent;

		virtual ~InputEvent();  // 00

		[[nodiscard]] virtual bool                 HasIDCode() const;   // 01 - { return false; }
		[[nodiscard]] virtual const BSFixedString& QUserEvent() const;  // 02 - { return ""; }

		[[nodiscard]] constexpr INPUT_EVENT_TYPE GetEventType() const noexcept { return *eventType; }
		[[nodiscard]] constexpr INPUT_DEVICE     GetDevice() const noexcept { return *device; }

		[[nodiscard]] ButtonEvent*       AsButtonEvent();
		[[nodiscard]] const ButtonEvent* AsButtonEvent() const;

		[[nodiscard]] IDEvent*       AsIDEvent();
		[[nodiscard]] const IDEvent* AsIDEvent() const;

		// members
		stl::enumeration<INPUT_DEVICE, std::uint32_t>     device;     // 08
		stl::enumeration<INPUT_EVENT_TYPE, std::uint32_t> eventType;  // 0C
		InputEvent*                                       next;       // 10
	};
	static_assert(sizeof(InputEvent) == 0x18);
}
