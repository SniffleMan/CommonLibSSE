#pragma once

#include "RE/N/NiFrustum.h"
#include "RE/N/NiFrustumPlanes.h"

namespace RE
{
	class BSDynamicTriShape;
	class BSFadeNode;
	class BSGeometry;
	class bhkAttachmentCollisionObject;
	class bhkBlendCollisionObject;
	class bhkLimitedHingeConstraint;
	class bhkNiCollisionObject;
	class bhkRigidBody;
	class BSLines;
	class BSMultiBoundNode;
	class BSSegmentedTriShape;
	class BSSubIndexTriShape;
	class BSTriShape;
	class NiAVObject;
	class NiCamera;
	class NiGeometry;
	class NiNode;
	class NiParticles;
	class NiSwitchNode;
	class NiRTTI;
	class NiTriBasedGeom;
	class NiTriShape;
	class NiTriStrips;
	class NiVisibleArray;

	class NiCullingProcess
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiCullingProcess;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiCullingProcess;

		// add
		[[nodiscard]] virtual const NiRTTI*                 GetRTTI() const;                      // 00
		virtual NiNode*                       GetAsNiNode();                        // 01 - { return 0; }
		virtual NiSwitchNode*                 GetAsNiSwitchNode();                  // 02 - { return 0; }
		virtual BSFadeNode*                   GetAsBSFadeNode();                    // 03 - { return 0; }
		virtual BSMultiBoundNode*             GetAsBSMultiBoundNode();              // 04 - { return 0; }
		virtual BSGeometry*                   GetAsBSGeometry();                    // 05 - { return 0; }
		virtual NiTriStrips*                  GetAsNiTriStrips();                   // 06 - { return 0; }
		virtual BSTriShape*                   GetAsBSTriShape();                    // 07 - { return 0; }
		virtual BSSegmentedTriShape*          GetAsBSSegmentedTriShape();           // 08 - { return 0; }
		virtual BSSubIndexTriShape*           GetAsBSSubIndexTriShape();            // 09 - { return 0; }
		virtual BSDynamicTriShape*            GetAsBSDynamicTriShape();             // 0A - { return 0; }
		virtual NiGeometry*                   GetAsNiGeometry();                    // 0B - { return 0; }
		virtual NiTriBasedGeom*               GetAsNiTriBasedGeom();                // 0C - { return 0; }
		virtual NiTriShape*                   GetAsNiTriShape();                    // 0D - { return 0; }
		virtual NiParticles*                  GetAsNiParticles();                   // 0E - { return 0; }
		virtual BSLines*                      GetAsBSLines();                       // 0F - { return 0; }
		virtual bhkNiCollisionObject*         GetAsBhkNiCollisionObject();          // 10 - { return 0; }
		virtual bhkBlendCollisionObject*      GetAsBhkBlendCollisionObject();       // 11 - { return 0; }
		virtual bhkAttachmentCollisionObject* GetAsBhkAttachmentCollisionObject();  // 12 - { return 0; }
		virtual bhkRigidBody*                 GetAsBhkRigidBody();                  // 13 - { return 0; }
		virtual bhkLimitedHingeConstraint*    GetAsBhkLimitedHingeConstraint();     // 14 - { return 0; }

		virtual ~NiCullingProcess();  // 15

		virtual void Process1(NiAVObject* a_object, std::uint32_t a_arg2);                                   // 16
		virtual void Process2(const NiCamera* a_camera, NiAVObject* a_scene, NiVisibleArray* a_visibleSet);  // 17 - { return; }
		virtual void AppendVirtual(BSGeometry& a_visible, std::uint32_t a_arg2);                             // 18

		// members
		const bool      useVirtualAppend;      // 008
		std::uint8_t    pad009;                // 009
		std::uint16_t   pad00A;                // 00A
		std::uint32_t   pad00C;                // 00C
		NiVisibleArray* visibleSet;            // 010
		const NiCamera* camera;                // 018
		NiFrustum       frustum;               // 020
		NiFrustumPlanes planes;                // 03C
		NiFrustumPlanes customCullPlanes;      // 0AC
		bool            cameraRelatedUpdates;  // 11C
		bool            updateAccumulateFlag;  // 11D
		bool            ignorePreprocess;      // 11E
		bool            doCustomCullPlanes;    // 11F
		std::uint8_t    unk120;                // 120
		std::uint8_t    unk121;                // 121
		std::uint16_t   pad122;                // 122
		std::uint32_t   pad124;                // 124
	};
	static_assert(sizeof(NiCullingProcess) == 0x128);
}
