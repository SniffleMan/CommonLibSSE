#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/B/BSFixedString.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class ExtraEditorID : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraEditorID;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kEditorID;

		~ExtraEditorID() override;  // 00

		// override (BSExtraData)
		[[nodiscard]] ExtraDataType GetType() const override;  // 01 - { return kEditorID; }

		// members
		BSFixedString editorID;  // 10
	};
	static_assert(sizeof(ExtraEditorID) == 0x18);
}
