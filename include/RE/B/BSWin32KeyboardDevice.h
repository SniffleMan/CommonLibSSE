#pragma once

#include "RE/B/BSKeyboardDevice.h"

namespace RE
{
	class BSWin32KeyboardDevice : public BSKeyboardDevice
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSWin32KeyboardDevice;

		~BSWin32KeyboardDevice() override;  // 00

		// override (BSKeyboardDevice)
		void Initialize() override;           // 01
		void Process(float a_unk1) override;  // 02
		void Unk_03(void) override;           // 03
		void Reset() override;                // 08 - { std::memset(&curState, 0, 0x200); }
		void Unk_09(void) override;           // 09 - { return; }
		void Unk_0A(void) override;           // 0A - { return; }

		[[nodiscard]] bool IsPressed(std::uint32_t a_keyCode) const;

		// members
		std::uint64_t unk070;            // 070
		std::uint64_t unk078;            // 078
		std::uint64_t unk080;            // 080
		std::uint64_t unk088;            // 088
		std::uint64_t unk090;            // 090
		std::uint64_t unk098;            // 098
		std::uint64_t unk0A0;            // 0A0
		std::uint64_t unk0A8;            // 0A8
		std::uint64_t unk0B0;            // 0B0
		std::uint64_t unk0B8;            // 0B8
		std::uint64_t unk0C0;            // 0C0
		std::uint64_t unk0C8;            // 0C8
		std::uint64_t unk0D0;            // 0D0
		std::uint64_t unk0D8;            // 0D8
		std::uint64_t unk0E0;            // 0E0
		std::uint64_t unk0E8;            // 0E8
		std::uint64_t unk0F0;            // 0F0
		std::uint64_t unk0F8;            // 0F8
		std::uint64_t unk100;            // 100
		std::uint64_t unk108;            // 108
		std::uint64_t unk110;            // 110
		std::uint64_t unk118;            // 118
		std::uint64_t unk120;            // 120
		std::uint64_t unk128;            // 128
		std::uint64_t unk130;            // 130
		std::uint64_t unk138;            // 138
		std::uint64_t unk140;            // 140
		std::uint64_t unk148;            // 148
		std::uint64_t unk150;            // 150
		std::uint64_t unk158;            // 158
		std::uint64_t unk160;            // 160
		std::uint8_t  curState[0x100];   // 168
		std::uint8_t  prevState[0x100];  // 268
		std::uint64_t unk368;            // 368
	};
	static_assert(offsetof(BSWin32KeyboardDevice, curState) == 0x168);
	static_assert(offsetof(BSWin32KeyboardDevice, prevState) == 0x268);
	static_assert(sizeof(BSWin32KeyboardDevice) == 0x370);
}
