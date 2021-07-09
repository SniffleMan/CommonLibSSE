#pragma once

#include "RE/N/NiAnimationKey.h"

namespace RE
{
	class NiFloatKey : public NiAnimationKey
	{
	public:
		NiFloatKey();
		NiFloatKey(float a_time, float a_value);
		~NiFloatKey();

		[[nodiscard]] float       GetValue() const;
		void        SetValue(float a_value);
		NiFloatKey* GetKeyAt(std::uint32_t a_index, std::uint8_t a_keySize);

	protected:
		float _value;  // 04
	};
	static_assert(sizeof(NiFloatKey) == 0x8);
}
