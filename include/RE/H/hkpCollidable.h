#pragma once

#include "RE/H/hkpCdBody.h"
#include "RE/H/hkpShape.h"
#include "RE/H/hkpTypedBroadPhaseHandle.h"

namespace RE
{
	class NiAVObject;

	struct hkAabbUint32;

	class hkpCollidable : public hkpCdBody
	{
	public:
		enum BelongsTo : std::uint32_t
		{
			kTerrain = 1 << 16
		};

		enum CollisionFilterInfo : std::uint32_t
		{
			kBelongsTo = 0xFFFF0000,
			kCollidesWith = 0x0000FFFF
		};

		enum class ForceCollideOntoPpuReasons
		{
			kUserRequest = 1 << 0,
			kShapeRequest = 1 << 1,
			kModifierRequest = 1 << 2,
			kShapeUnchecked = 1 << 3
		};

		struct BoundingVolumeData
		{
		public:
			// members
			std::uint32_t min[3];					// 00
			std::uint8_t  expansionMin[3];			// 0C
			std::uint8_t  expansionShift;			// 0F
			std::uint32_t max[3];					// 10
			std::uint8_t  expansionMax[3];			// 1C
			std::uint8_t  pad1F;					// 1F
			std::uint16_t numChildShapeAabbs;		// 20
			std::uint16_t capacityChildShapeAabbs;	// 22
			std::uint32_t pad24;					// 24
			hkAabbUint32* childShapeAabbs;			// 28
			hkpShapeKey*  childShapeKeys;			// 30
		};
		static_assert(sizeof(BoundingVolumeData) == 0x38);

		NiAVObject* Get3D() const;

		void* GetOwner() const;
		template <class T>
		T* GetOwner() const
		{
			return static_cast<T*>(GetOwner());
		}

		// members
		std::int8_t				 ownerOffset;			   // 20
		std::uint8_t			 forceCollideOntoPpu;	   // 21
		std::uint16_t			 shapeSizeOnSpu;		   // 22
		hkpTypedBroadPhaseHandle broadPhaseHandle;		   // 24
		BoundingVolumeData		 boundingVolumeData;	   // 30
		float					 allowedPenetrationDepth;  // 68
		std::uint32_t			 pad6C;					   // 6C
	};
	static_assert(sizeof(hkpCollidable) == 0x70);
}
