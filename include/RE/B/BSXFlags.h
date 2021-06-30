#pragma once

#include "RE/N/NiIntegerExtraData.h"

namespace RE
{
	class BSXFlags : public NiIntegerExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSXFlags;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSXFlags;

		enum class Flag
		{
			kNone = 0,
			kAnimated = 1 << 0,
			kHavok = 1 << 1,
			kRagdoll = 1 << 2,
			kComplex = 1 << 3,
			kAddon = 1 << 4,
			kEditorMarker = 1 << 5,
			kDynamic = 1 << 6,
			kArticulated = 1 << 7,
			kNeedsTransformUpdate = 1 << 8,
			kExternalEmit = 1 << 9,
			kMagicShaderParticles = 1 << 10,
			kLights = 1 << 11,
			kBreakable = 1 << 12,
			kSearchedBreakable = 1 << 13
		};

		~BSXFlags() override;  // 00

		// override (NiIntegerExtraData)
		const NiRTTI* GetRTTI() const override;                           // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17 - { return this; }
		void          LoadBinary(NiStream& a_stream) override;            // 18 - { NiIntegerExtraData::LoadBinary(a_stream); }
		void          LinkObject(NiStream& a_stream) override;            // 19 - { NiIntegerExtraData::LinkObject(a_stream); }
		bool          RegisterStreamables(NiStream& a_stream) override;   // 1A - { return NiIntegerExtraData::RegisterStreamables(a_stream); }
		void          SaveBinary(NiStream& a_stream) override;            // 1B - { NiIntegerExtraData::SaveBinary(a_stream); }
		bool          IsEqual(NiObject* a_object) override;               // 1C - { return NiIntegerExtraData::IsEqual(a_object); }

		[[nodiscard]] Flag GetFlags() const;
		void SetFlags(Flag a_flags);
	};
	static_assert(sizeof(BSXFlags) == 0x20);
}
