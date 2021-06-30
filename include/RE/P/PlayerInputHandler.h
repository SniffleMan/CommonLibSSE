#pragma once

namespace RE
{
	class ButtonEvent;
	class InputEvent;
	class MouseMoveEvent;
	class PlayerControlsData;
	class ThumbstickEvent;

	class PlayerInputHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_PlayerInputHandler;

		virtual ~PlayerInputHandler();  // 00

		virtual bool CanProcess(InputEvent* a_event) = 0;                                      // 01
		virtual void ProcessThumbstick(ThumbstickEvent* a_event, PlayerControlsData* a_data);  // 02 - { return; }
		virtual void ProcessMouseMove(MouseMoveEvent* a_event, PlayerControlsData* a_data);    // 03 - { return; }
		virtual void ProcessButton(ButtonEvent* a_event, PlayerControlsData* a_data);          // 04 - { return; }

		[[nodiscard]] bool IsInputEventHandlingEnabled() const;
		void SetInputEventHandlingEnabled(bool a_enabled);

		// members
		bool          inputEventHandlingEnabled;  // 08
		std::uint8_t  pad09;                      // 09
		std::uint16_t pad0A;                      // 0A
		std::uint32_t pad0C;                      // 0C
	};
	static_assert(sizeof(PlayerInputHandler) == 0x10);
}
