#pragma once

#include "RE/F/FormTypes.h"
#include "RE/T/TESObjectMISC.h"

namespace RE
{
	class TESKey : public TESObjectMISC
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESKey;
		inline static constexpr auto FORMTYPE = FormType::KeyMaster;

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kNonPlayable = 1 << 2,
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		~TESKey() override;  // 00

		// override (BGSKeywordForm)
		[[nodiscard]] BGSKeyword* GetDefaultKeyword() const override;  // 05
	};
	static_assert(sizeof(TESKey) == 0x100);
}
