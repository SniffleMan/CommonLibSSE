#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class TESPackage;

	class ExtraPackage : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraPackage;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kPackage;

		~ExtraPackage() override;  // 00

		// override (BSExtraData)
		[[nodiscard]] ExtraDataType GetType() const override;  // 01 - { return kPackage; }

		// members
		TESPackage*     unk10;           // 10
		std::int32_t    index;           // 18
		ObjectRefHandle target;          // 1C
		bool            actionComplete;  // 20
		bool            activated;       // 21
		bool            doneOnce;        // 22
		std::uint8_t    unk23;           // 23
		std::uint32_t   unk24;           // 24
	};
	static_assert(sizeof(ExtraPackage) == 0x28);
}
