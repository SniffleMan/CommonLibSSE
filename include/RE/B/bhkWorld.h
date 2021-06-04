#pragma once

#include "RE/B/bhkSerializable.h"

namespace RE
{
	struct hkpWorldRayCastInput;

	class bhkWorld : public bhkSerializable
	{
	public:
		inline static constexpr auto RTTI = RTTI_bhkWorld;
		inline static constexpr auto Ni_RTTI = NiRTTI_bhkWorld;

		virtual ~bhkWorld();  // 00

		// add
		virtual void Unk_32(void);										  // 32
		virtual bool CastRay(hkpWorldRayCastInput& a_worldRayCastInput);  // 33
		virtual void Unk_34(void);										  // 34
		virtual void Unk_35(void);										  // 35
		virtual void Unk_36(void);										  // 36

		static float GetWorldScale()
		{
			REL::Relocation<float*> worldScale{ REL::ID(231896) };
			return *worldScale;
		}

		static float GetWorldScaleInverse()
		{
			REL::Relocation<float*> worldScaleInverse{ REL::ID(230692) };
			return *worldScaleInverse;
		}

		// members
		std::uint8_t unk0020[0xC600 - 0x0020];	// 0020
	};
	static_assert(sizeof(bhkWorld) == 0xC600);
}
