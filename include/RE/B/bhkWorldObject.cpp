#include "RE/B/bhkWorldObject.h"

#include "RE/H/hkpWorldObject.h"

namespace RE
{
	void* bhkWorldObject::GetPropertyValue(std::uint32_t a_key) const
	{
		return static_cast<hkpWorldObject*>(referencedObject.get())->GetPropertyValue(a_key);
	}
}
