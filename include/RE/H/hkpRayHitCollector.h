#pragma once

namespace RE
{
	class hkpRayHitCollector
	{
	public:
		hkpRayHitCollector() noexcept = default;

		hkpRayHitCollector(void* a_vtbl) noexcept :
			vtbl(a_vtbl){};

		// members
		void*		  vtbl{ 0 };					// 0
		float		  earlyOutHitFraction{ 1.0F };	// 8
		std::uint32_t padC;							// C
	};
	static_assert(sizeof(hkpRayHitCollector) == 0x10);
}
