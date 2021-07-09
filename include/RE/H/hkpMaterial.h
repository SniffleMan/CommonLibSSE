#pragma once

#include "RE/H/hkBaseTypes.h"

namespace RE
{
	class hkpMaterial
	{
	public:
		enum class ResponseType
		{
			kInvalid,
			kSimpleContact,
			kReporting,
			kNone,

			kTotal
		};

		[[nodiscard]] ResponseType GetResponseType() const;
		void         SetResponseType(ResponseType a_type);

		// members
		stl::enumeration<ResponseType, std::uint8_t> responseType;               // 00
		std::uint8_t                                 pad01;                      // 01
		hkHalf                                       rollingFrictionMultiplier;  // 02
		float                                        friction;                   // 04
		float                                        restitution;                // 08
	};
	static_assert(sizeof(hkpMaterial) == 0xC);
}
