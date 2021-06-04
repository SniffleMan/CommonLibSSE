#pragma once

#include "RE/B/bhkNiCollisionObject.h"

namespace RE
{
	class bhkRigidBody;

	class bhkCollisionObject : public bhkNiCollisionObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_bhkCollisionObject;
		inline static constexpr auto Ni_RTTI = NiRTTI_bhkCollisionObject;

		virtual ~bhkCollisionObject();	// 00

		// override (bhkNiCollisionObject)
		virtual const NiRTTI* GetRTTI() const override;							  // 02
		virtual NiObject*	  CreateClone(NiCloningProcess& a_cloning) override;  // 17
		virtual void		  LoadBinary(NiStream& a_stream) override;			  // 18 - { bhkNiCollisionObject::LoadBinary(a_stream); }
		virtual void		  LinkObject(NiStream& a_stream) override;			  // 19 - { bhkNiCollisionObject::LinkObject(a_stream); }
		virtual bool		  RegisterStreamables(NiStream& a_stream) override;	  // 1A - { return bhkNiCollisionObject::RegisterStreamables(a_stream); }
		virtual void		  SaveBinary(NiStream& a_stream) override;			  // 1B - { bhkNiCollisionObject::SaveBinary(a_stream); }
		virtual void		  Unk_26(void) override;							  // 26
		virtual void		  Unk_2A(void) override;							  // 2A
		virtual void		  Unk_2B(void) override;							  // 2B
		virtual void		  Unk_2C(void) override;							  // 2C
		virtual void		  Unk_2D(void) override;							  // 2D
		virtual void		  Unk_2E(void) override;							  // 2E
		virtual void		  Unk_2F(void) override;							  // 2F

		bhkRigidBody* GetRigidBody() const
		{
			using func_t = decltype(&bhkCollisionObject::GetRigidBody);
			REL::Relocation<func_t> func{ REL::ID(12784) };
			return func(this);
		}
	};
	static_assert(sizeof(bhkCollisionObject) == 0x28);
}
