#pragma once

#include "RE/H/hkpShape.h"

namespace RE
{
	class hkpCdBody
	{
	public:
		[[nodiscard]] const hkpShape* GetShape() const;

		// members
		const hkpShape*  shape;     // 00
		hkpShapeKey      shapeKey;  // 08
		std::uint32_t    pad0C;     // 0C
		const void*      motion;    // 10
		const hkpCdBody* parent;    // 18
	};
	static_assert(sizeof(hkpCdBody) == 0x20);
}
