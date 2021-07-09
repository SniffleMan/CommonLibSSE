#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class ExtraInfoGeneralTopic : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraInfoGeneralTopic;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kInfoGeneralTopic;

		struct Data
		{
			std::uint64_t unk00;  // 00
			std::uint64_t unk08;  // 08
			std::uint64_t unk10;  // 10
			std::uint64_t unk18;  // 18
			std::uint64_t unk20;  // 20
			std::uint64_t unk28;  // 28
			std::uint64_t unk30;  // 30
			std::uint64_t unk38;  // 38
			std::uint64_t unk40;  // 40
			std::uint64_t unk48;  // 48
			std::uint64_t unk50;  // 50
		};
		static_assert(sizeof(Data) == 0x58);

		~ExtraInfoGeneralTopic() override;  // 00

		// override (BSExtraData)
		[[nodiscard]] ExtraDataType GetType() const override;  // 01 - { return kInfoGeneralTopic; }

		// members
		Data* unk10;  // 10
	};
	static_assert(sizeof(ExtraInfoGeneralTopic) == 0x18);
}
