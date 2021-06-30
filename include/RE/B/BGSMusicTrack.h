#pragma once

#include "RE/B/BSIMusicTrack.h"
#include "RE/T/TESCondition.h"

namespace RE
{
	class TESFile;
	class TESForm;

	class BGSMusicTrack : public BSIMusicTrack
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSMusicTrack;

		~BGSMusicTrack() override;  // 00

		// override (BSIMusicTrack)
		[[nodiscard]] bool TestCanPlay() const override;  // 07 - { return conditions ? conditions->Run(g_thePlayer, g_thePlayer) : true; }

		// add
		virtual void InitItem(TESForm* a_form);  // 0B
		virtual void Load(TESFile* a_mod) = 0;   // 0C

		// members
		TESCondition  conditions;  // 10
		std::uint64_t unk18;       // 18
	};
	static_assert(sizeof(BGSMusicTrack) == 0x20);
}
