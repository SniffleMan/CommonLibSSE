#pragma once

#include "RE/B/BSTArray.h"
#include "RE/B/BSTempEffect.h"
#include "RE/N/NiColor.h"
#include "RE/N/NiFrustumPlanes.h"
#include "RE/N/NiMatrix3.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class BGSDecalNode;
	class BGSTextureSet;
	class BSTriShape;
	class NiAVObject;

	class BSTempEffectSimpleDecal : public BSTempEffect
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSTempEffectSimpleDecal;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSTempEffectSimpleDecal;

		~BSTempEffectSimpleDecal() override;  // 00

		const NiRTTI* GetRTTI() const override;       // 02
		void          Initialize() override;          // 25
		void          Attach() override;              // 26
		bool          Update(float a_arg1) override;  // 28
		[[nodiscard]] NiAVObject*   Get3D() const override;         // 29

		// members
		std::uint8_t            unk30;            // 030
		std::uint8_t            unk31;            // 031
		bool                    unk32;            // 032
		std::uint16_t           unk36;            // 036
		std::uint64_t           unk38;            // 038
		std::uint32_t           unk40;            // 040
		std::uint32_t           unk44;            // 044
		NiPointer<BSGeometry>   effect3D;         // 048
		std::uint32_t           unk50;            // 050
		bool                    permanent;        // 054
		std::uint8_t            unk55;            // 055
		bool                    unk56;            // 056
		std::uint8_t            unk57;            // 057
		BGSTextureSet*          textureSet;       // 058
		BGSTextureSet*          textureSet2;      // 060
		NiPoint3                origin1;          // 068
		NiPoint3                direction1;       // 074
		NiPoint3                origin2;          // 080 - copy?
		NiPoint3                direction2;       // 08C - copy?
		NiFrustumPlanes         planes;           // 098
		std::uint64_t           unk108;           // 108
		std::uint64_t           unk110;           // 110
		std::uint64_t           unk118;           // 118
		std::uint64_t           unk120;           // 120
		std::uint64_t           unk128;           // 128
		std::uint64_t           unk130;           // 130
		std::uint64_t           unk138;           // 138
		std::uint64_t           unk140;           // 140
		std::uint64_t           unk148;           // 148
		std::uint64_t           unk150;           // 150
		BSTArray<void*>         unk158;           // 158 - triangle data?
		NiPointer<BGSDecalNode> decalNode;        // 170
		NiPointer<BSTriShape>   avShape;          // 178
		float                   unk180;           // 180
		NiMatrix3               emitterRotation;  // 184
		std::uint32_t           unk1A8;           // 1A8
		float                   width;            // 1AC
		float                   height;           // 1B0
		float                   depth;            // 1B4;
		std::uint8_t            subTextureIndex;  // 1B8
		bool                    parallaxOcc;      // 1B9
		std::uint8_t            unk1BA;           // 1BA
		std::uint8_t            unk1BB;           // 1BB
		float                   parallaxScale;    // 1BC
		std::uint8_t            parallaxPasses;   // 1C0
		bool                    alphaBlending;    // 1C1
		bool                    enableBlending;   // 1C2
		std::uint8_t            unk1C3;           // 1C3
		float                   shininess;        // 1C4
		NiColor                 color;            // 1C8
		bool                    unk1D4;           // 1D4
		bool                    twoSided;         // 1D5
		bool                    unk1D6;           // 1D6
		std::uint8_t            unk1D7;           // 1D7
		std::uint32_t           unk1D8;           // 1D8
		std::uint32_t           unk1DC;           // 1DC
	};
	static_assert(sizeof(BSTempEffectSimpleDecal) == 0x1E0);
};
