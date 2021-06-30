#pragma once

#include "RE/N/NiRefObject.h"
#include "RE/N/NiSmartPointer.h"

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
	class NiCloningProcess;
	class NiControllerManager;
	class NiGeometry;
	class NiNode;
	class NiObjectGroup;
	class NiParticles;
	class NiRTTI;
	class NiStream;
	class NiSwitchNode;
	class NiTriBasedGeom;
	class NiTriShape;
	class NiTriStrips;

	NiSmartPointer(NiObject);

	class NiObject : public NiRefObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiObject;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiObject;

		~NiObject() override = default;  // 00

		// add
		[[nodiscard]] virtual const NiRTTI*                 GetRTTI() const;                                                            // 02
		virtual NiNode*                       AsNode() { return nullptr; }                                                // 03
		virtual NiSwitchNode*                 AsSwitchNode() { return nullptr; }                                          // 04
		virtual BSFadeNode*                   AsFadeNode() { return nullptr; }                                            // 05
		virtual BSMultiBoundNode*             AsMultiBoundNode() { return nullptr; }                                      // 06
		virtual BSGeometry*                   AsGeometry() { return nullptr; }                                            // 07
		virtual NiTriStrips*                  AsTriStrips() { return nullptr; }                                           // 08
		virtual BSTriShape*                   AsTriShape() { return nullptr; }                                            // 09
		virtual BSSegmentedTriShape*          AsSegmentedTriShape() { return nullptr; }                                   // 0A
		virtual BSSubIndexTriShape*           AsSubIndexTriShape() { return nullptr; }                                    // 0B
		virtual BSDynamicTriShape*            AsDynamicTriShape() { return nullptr; }                                     // 0C
		virtual NiGeometry*                   AsNiGeometry() { return nullptr; }                                          // 0D
		virtual NiTriBasedGeom*               AsNiTriBasedGeom() { return nullptr; }                                      // 0E
		virtual NiTriShape*                   AsNiTriShape() { return nullptr; }                                          // 0F
		virtual NiParticles*                  AsParticlesGeom() { return nullptr; }                                       // 10
		virtual BSLines*                      AsLinesGeom() { return nullptr; }                                           // 11
		virtual bhkNiCollisionObject*         AsBhkNiCollisionObject() { return nullptr; }                                // 12
		virtual bhkBlendCollisionObject*      AsBhkBlendCollisionObject() { return nullptr; }                             // 13
		virtual bhkAttachmentCollisionObject* AsBhkAttachmentCollisionObject() { return nullptr; }                        // 14
		virtual bhkRigidBody*                 AsBhkRigidBody() { return nullptr; }                                        // 15
		virtual bhkLimitedHingeConstraint*    AsBhkLimitedHingeConstraint() { return nullptr; }                           // 16
		virtual NiObject*                     CreateClone([[maybe_unused]] NiCloningProcess& a_cloning) { return this; }  // 17
		virtual void                          LoadBinary([[maybe_unused]] NiStream& a_stream) { return; }                 // 18
		virtual void                          LinkObject([[maybe_unused]] NiStream& a_stream) { return; }                 // 19
		virtual bool                          RegisterStreamables(NiStream& a_stream);                                    // 1A
		virtual void                          SaveBinary([[maybe_unused]] NiStream& a_stream) { return; }                 // 1B
		virtual bool                          IsEqual(NiObject* a_object);                                                // 1C
		virtual void                          ProcessClone(NiCloningProcess& a_cloning);                                  // 1D
		virtual void                          PostLinkObject([[maybe_unused]] NiStream& a_stream) { return; }             // 1E
		virtual bool                          StreamCanSkip() { return false; }                                           // 1F
		[[nodiscard]] virtual const NiRTTI*                 GetStreamableRTTI() const { return GetRTTI(); }                             // 20
		[[nodiscard]] virtual std::uint32_t                 GetBlockAllocationSize() const { return 0; }                                // 21
		[[nodiscard]] virtual NiObjectGroup*                GetGroup() const { return nullptr; }                                        // 22
		virtual void                          SetGroup([[maybe_unused]] NiObjectGroup* a_group) { return; }               // 23
		virtual NiControllerManager*          AsNiControllerManager() { return nullptr; }                                 // 24

		void CreateDeepCopy(NiPointer<NiObject>& a_object);
	};
	static_assert(sizeof(NiObject) == 0x10);
}
