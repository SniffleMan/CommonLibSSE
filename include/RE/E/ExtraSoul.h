#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"
#include "RE/S/SoulLevels.h"

namespace RE
{
	class ExtraSoul : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraSoul;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kSoul;

		ExtraSoul();
		explicit ExtraSoul(SOUL_LEVEL a_level);
		~ExtraSoul() override = default;  // 00

		// override (BSExtraData)
		ExtraDataType GetType() const override;                             // 01 - { reutrn kSoul; }
		bool          IsNotEqual(const BSExtraData* a_rhs) const override;  // 02 - { return soul != a_rhs->soul; }

		[[nodiscard]] SOUL_LEVEL GetContainedSoul() const;

		// members
		stl::enumeration<SOUL_LEVEL, std::uint8_t> soul;   // 10
		std::uint8_t                               pad11;  // 11
		std::uint16_t                              pad12;  // 12
		std::uint32_t                              pad14;  // 14
	};
	static_assert(sizeof(ExtraSoul) == 0x18);
}
