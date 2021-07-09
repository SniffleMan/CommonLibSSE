#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/I/InputEvent.h"

namespace RE
{
	class IDEvent : public InputEvent
	{
	public:
		inline static constexpr auto RTTI = RTTI_IDEvent;

		~IDEvent() override;  // 00

		// override
		bool                 HasIDCode() const override;   // 01 - { return true; }
		[[nodiscard]] const BSFixedString& QUserEvent() const override;  // 02 - { return userEvent; }

		[[nodiscard]] constexpr std::uint32_t GetIDCode() const noexcept { return idCode; }

		// members
		BSFixedString userEvent;  // 18
		std::uint32_t idCode;     // 20
		std::uint32_t pad24;      // 24
	};
	static_assert(sizeof(IDEvent) == 0x28);
}
