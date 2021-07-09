#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class ExtraRefrPath : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraRefrPath;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kRefrPath;

		enum class PATH_TYPE
		{
		};

		~ExtraRefrPath() override;  // 00

		// override (BSExtraData)
		[[nodiscard]] ExtraDataType GetType() const override;  // 01 - { return kRefrPath; }

		// members
		NiPoint3                                   startPos;          // 10
		NiPoint3                                   startTangent;      // 1C
		NiPoint3                                   startEuler;        // 28
		NiPoint3                                   goalPos;           // 34
		NiPoint3                                   goalTangent;       // 40
		NiPoint3                                   goalEuler;         // 4C
		float                                      speed;             // 58
		float                                      maxRotSpeed;       // 5C
		float                                      currentParameter;  // 60
		stl::enumeration<PATH_TYPE, std::uint32_t> type;              // 64
	};
	static_assert(sizeof(ExtraRefrPath) == 0x68);
}
