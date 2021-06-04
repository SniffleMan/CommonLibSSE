#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkMultiThreadCheck.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkStringPtr.h"
#include "RE/H/hkpLinkedCollidable.h"
#include "RE/H/hkpProperty.h"

namespace RE
{
	class hkMotionState;
	class hkpCollidable;
	class hkpShapeModifier;
	class hkpWorld;

	namespace hkWorldOperation
	{
		enum class Result
		{
			kPostponed,
			kDone
		};
	}

	class hkpWorldObject : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkpWorldObject;

		enum class MultiThreadingChecks
		{
			kEnable,
			kIgnore
		};

		enum class BroadPhaseType
		{
			kInvalid,
			kEntity,
			kPhantom,
			kPhaseBorder,

			kTotal
		};

		virtual ~hkpWorldObject();	// 00

		// override (hkReferencedObject)
		virtual void CalcContentStatistics(hkStatisticsCollector* a_collector, const hkClass* a_class) const override;	// 02

		// add
		virtual hkWorldOperation::Result SetShape(const hkpShape* a_shape);				  // 03 - { return hkWorldOperation::Result::kDone; }
		virtual hkWorldOperation::Result UpdateShape(hkpShapeModifier* a_shapeModifier);  // 04 - { return hkWorldOperation::Result::kDone; }
		virtual hkMotionState*			 GetMotionState() = 0;							  // 05

		const hkpCollidable* GetCollidable() const;
		hkpCollidable*		 GetCollidableRW();

		void* GetPropertyValue(std::uint32_t a_key) const
		{
			auto size = properties.size();
			if (size > 0) {
				for (auto property : properties) {
					if (property.key == a_key) {
						return reinterpret_cast<void*>(property.value.data);
					}
				}
			}

			return nullptr;
		}

		template <class T>
		T* GetPropertyValue(std::uint32_t a_key) const
		{
			return static_cast<T*>(GetPropertyValue(a_key));
		}

		// members
		hkpWorld*			 world;				// 10
		std::uint64_t		 userData;			// 18 - bhkWorldObject*?
		hkpLinkedCollidable	 collidable;		// 20
		hkMultiThreadCheck	 multiThreadCheck;	// A0
		std::uint32_t		 padAC;				// AC
		hkStringPtr			 name;				// B0
		hkArray<hkpProperty> properties;		// B8
		void*				 treeData;			// C8
	};
	static_assert(sizeof(hkpWorldObject) == 0xD0);
}
