#include "RE/H/hkpCollidable.h"

#include "RE/B/bhkCollisionObject.h"
#include "RE/B/bhkWorldObject.h"
#include "RE/H/hkpWorldObject.h"

namespace RE
{
	NiAVObject* hkpCollidable::Get3D() const
	{
		auto owner = GetOwner<hkpWorldObject>();
		if (!owner) {
			return nullptr;
		}

		auto propertyValue = owner->GetPropertyValue<bhkCollisionObject>(2);
		if (propertyValue) {
			return propertyValue->sceneObject;
		}

		auto userData = reinterpret_cast<bhkWorldObject*>(owner->userData);
		if (userData) {
			return userData->GetPropertyValue<NiAVObject>(1);
		}

		return nullptr;
	}
	
	void* hkpCollidable::GetOwner() const
	{
		return const_cast<void*>(adjust_pointer<const void>(this, ownerOffset));
	}
}
