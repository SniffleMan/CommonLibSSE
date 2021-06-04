#pragma once

#include "RE/H/hkpRayHitCollector.h"
#include "RE/H/hkpWorldRayCastOutput.h"

namespace RE
{
	class hkpClosestRayHitCollector : public hkpRayHitCollector
	{
	public:
		hkpClosestRayHitCollector() noexcept :
			hkpRayHitCollector(reinterpret_cast<void*>(REL::ID(242710).address())){};

		// members
		hkpWorldRayCastOutput rayHit;  // 10
	};
	static_assert(sizeof(hkpClosestRayHitCollector) == 0x70);
}
