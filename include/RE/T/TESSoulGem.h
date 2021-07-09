#pragma once

#include "RE/F/FormTypes.h"
#include "RE/S/SoulLevels.h"
#include "RE/T/TESObjectMISC.h"

namespace RE
{
	class TESSoulGem : public TESObjectMISC
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESSoulGem;
		inline static constexpr auto FORMTYPE = FormType::SoulGem;

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12,
				kCanHoldNPCSoul = 1 << 17
			};
		};

		~TESSoulGem() override;  // 00

		// override (TESObjectMISC)
		void InitializeData() override;                                   // 04
		void LoadImpl(TESFile* a_mod, std::uint32_t a_chunkID) override;  // 54
		void InitImpl() override;                                         // 55

		// override (BGSKeywordForm)
		[[nodiscard]] BGSKeyword* GetDefaultKeyword() const override;  // 05

		[[nodiscard]] constexpr SOUL_LEVEL GetContainedSoul() const noexcept { return *currentSoul; }
		[[nodiscard]] constexpr SOUL_LEVEL GetMaximumCapacity() const noexcept { return *soulCapacity; }

		// members
		TESSoulGem*                                linkedSoulGem;  // 100 - NAM0
		stl::enumeration<SOUL_LEVEL, std::uint8_t> currentSoul;    // 108 - SOUL
		stl::enumeration<SOUL_LEVEL, std::uint8_t> soulCapacity;   // 109 - SLCP
		std::uint16_t                              unk10A;         // 10A
		std::uint32_t                              unk10C;         // 10C
	};
	static_assert(sizeof(TESSoulGem) == 0x110);
}
