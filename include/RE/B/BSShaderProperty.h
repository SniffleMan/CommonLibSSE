#pragma once

#include "RE/B/BSEffectShaderData.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/N/NiShadeProperty.h"

namespace RE
{
	class BSShaderMaterial;

	class BSShaderProperty : public NiShadeProperty
	{
	private:
		static constexpr auto BIT64 = static_cast<std::uint64_t>(1);

	public:
		inline static constexpr auto RTTI = RTTI_BSShaderProperty;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSShaderProperty;

		enum class EShaderPropertyFlag : std::uint64_t
		{
			kSpecular = BIT64 << 0,
			kSkinned = BIT64 << 1,
			kTempRefraction = BIT64 << 2,
			kVertexAlpha = BIT64 << 3,
			kGrayscaleToPaletteColor = BIT64 << 4,
			kGrayscaleToPaletteAlpha = BIT64 << 5,
			kFalloff = BIT64 << 6,
			kEnvMap = BIT64 << 7,
			kRGBFalloff = BIT64 << 8,
			kCastShadows = BIT64 << 9,
			kFace = BIT64 << 10,
			kUIMaskRects = BIT64 << 11,
			kModelSpaceNormals = BIT64 << 12,
			kRefractionClamp = BIT64 << 13,
			kMultiTextureLandscape = BIT64 << 14,
			kRefraction = BIT64 << 15,
			kRefractionFalloff = BIT64 << 16,
			kEyeReflect = BIT64 << 17,
			kHairTint = BIT64 << 18,
			kScreendoorAlphaFade = BIT64 << 19,
			kLocalMapClear = BIT64 << 20,
			kFaceGenRGBTint = BIT64 << 21,
			kOwnEmit = BIT64 << 22,
			kProjectedUV = BIT64 << 23,
			kMultipleTextures = BIT64 << 24,
			kTesselate = BIT64 << 25,
			kDecal = BIT64 << 26,
			kDynamicDecal = BIT64 << 27,
			kCharacterLight = BIT64 << 28,
			kExternalEmittance = BIT64 << 29,
			kSoftEffect = BIT64 << 30,
			kZBufferTest = BIT64 << 31,
			kZBufferWrite = BIT64 << 32,
			kLODLandscape = BIT64 << 33,
			kLODObjects = BIT64 << 34,
			kNoFade = BIT64 << 35,
			kTwoSided = BIT64 << 36,
			kVertexColors = BIT64 << 37,
			kGlowMap = BIT64 << 38,
			kTransformChanged = BIT64 << 39,
			kDismembermentMeatCuff = BIT64 << 40,
			kTint = BIT64 << 41,
			kVertexLighting = BIT64 << 42,
			kUniformScale = BIT64 << 43,
			kFitSlope = BIT64 << 44,
			kBillboard = BIT64 << 45,
			kLODLandBlend = BIT64 << 46,
			kDismemberment = BIT64 << 47,
			kWireframe = BIT64 << 48,
			kWeaponBlood = BIT64 << 49,
			kHideOnLocalMap = BIT64 << 50,
			kPremultAlpha = BIT64 << 51,
			kVATSTarget = BIT64 << 52,
			kAnisotropicLighting = BIT64 << 53,
			kSkewSpecularAlpha = BIT64 << 54,
			kMenuScreen = BIT64 << 55,
			kMultiLayerParallax = BIT64 << 56,
			kAlphaTest = BIT64 << 57,
			kInvertedFadePattern = BIT64 << 58,
			kVATSTargetDrawAll = BIT64 << 59,
			kPipboyScreen = BIT64 << 60,
			kTreeAnim = BIT64 << 61,
			kEffectLighting = BIT64 << 62,
			kRefractionWritesDepth = BIT64 << 63
		};

		~BSShaderProperty() override;  // 00

		// override (NiShadeProperty)
		const NiRTTI* GetRTTI() const override;                           // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17 - { return 0; }
		void          LoadBinary(NiStream& a_stream) override;            // 18
		void          LinkObject(NiStream& a_stream) override;            // 19 - { NiShadeProperty::LinkObject(a_stream); }
		bool          RegisterStreamables(NiStream& a_stream) override;   // 1A - { return NiShadeProperty::RegisterStreamables(a_stream); }
		void          SaveBinary(NiStream& a_stream) override;            // 1B
		bool          IsEqual(NiObject* a_object) override;               // 1C - { return false; }
		void          PostLinkObject(NiStream& a_stream) override;        // 1E - { NiObjectNET::PostLinkObject(a_stream); }
		void          Unk_27(void) override;                              // 27 - { return 1; }
		void          Unk_29(void) override;                              // 29

		// add
		virtual void Unk_2A(void) = 0;           // 2A
		virtual void Unk_2B(void);               // 2B - { return 0; }
		virtual void Unk_2C(void);               // 2C - { return 0; }
		virtual void Unk_2D(void);               // 2D - { return 0; }
		virtual void Unk_2E(void);               // 2E - { return 1; }
		virtual void Unk_2F(void);               // 2F - { return 0; }
		virtual void Unk_30(void);               // 30
		virtual void Unk_31(void);               // 31 - { return; }
		virtual void Unk_32(void);               // 32 - { return 1.0; }
		virtual void Unk_33(void);               // 33 - { return 1; }
		virtual void Unk_34(void);               // 34
		virtual void Unk_35(void);               // 35 - { return 0; }
		virtual void Unk_36(void);               // 36 - { return 0; }
		virtual void Unk_37(void);               // 37 - { return 0; }
		virtual void Unk_38(void);               // 38 - { return 0; }
		[[nodiscard]] virtual bool AcceptsEffectData() const;  // 39 - { return false; }
		virtual void Unk_3A(void);               // 3A - { return; }
		virtual void Unk_3B(void);               // 3B - { return; }
		virtual void Unk_3C(void);               // 3C - { return 0; }
		virtual void Unk_3D(void);               // 3D - { return 0; }
		virtual void Unk_3E(void);               // 3E - { return 0; }

		void SetEffectShaderData(const BSTSmartPointer<BSEffectShaderData>& a_data);

		// members
		float                                                alpha;                // 30
		std::int32_t                                         lastRenderPassState;  // 34
		stl::enumeration<EShaderPropertyFlag, std::uint64_t> flags;                // 38
		void*                                                unk40;                // 40
		std::uint64_t                                        unk48;                // 48
		void*                                                unk50;                // 50
		std::uint64_t                                        unk58;                // 58
		std::uint64_t                                        unk60;                // 60
		BSTSmartPointer<BSEffectShaderData>                  effectData;           // 68
		std::uint64_t                                        unk70;                // 70
		BSShaderMaterial*                                    material;             // 78
		std::uint64_t                                        unk80;                // 80
	};
	static_assert(sizeof(BSShaderProperty) == 0x88);
}
