#pragma once

#include "RE/H/hkVector4.h"
#include "RE/H/hkpWorldRayCastOutput.h"

namespace RE
{
	class hkpRayHitCollector;

	struct hkpWorldRayCastInput
	{
	public:
		// members
		hkVector4			  from;									 // 00
		hkVector4			  to;									 // 10
		bool				  enableShapeCollectionFilter{ false };	 // 20
		std::uint32_t		  filterInfo{ 0 };						 // 24
		hkpWorldRayCastOutput rayHit;								 // 30
		hkVector4			  ray;									 // 90
		hkpRayHitCollector*	  rayHitCollectorA0{ nullptr };			 // A0
		hkpRayHitCollector*	  rayHitCollectorA8{ nullptr };			 // A8
		hkpRayHitCollector*	  rayHitCollectorB0{ nullptr };			 // B0
		hkpRayHitCollector*	  rayHitCollectorB8{ nullptr };			 // B8
		bool				  unkC0{ false };						 // C0
		std::uint8_t		  padC1;								 // C1
		std::uint16_t		  padC2;								 // C2
		std::uint32_t		  padC4;								 // C4
		std::uint64_t		  padC8;								 // C8
	};
	static_assert(sizeof(hkpWorldRayCastInput) == 0xD0);
}
