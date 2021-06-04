#pragma once

#include "RE/B/bhkSerializable.h"
#include "RE/H/hkpShape.h"

namespace RE
{
	class bhkShape : public bhkSerializable
	{
	public:
		inline static constexpr auto RTTI = RTTI_bhkShape;
		inline static constexpr auto Ni_RTTI = NiRTTI_bhkShape;

		virtual ~bhkShape();  // 00

		// override (bhkSerializable)
		virtual const NiRTTI* GetRTTI() const override;							 // 02
		virtual void		  LoadBinary(NiStream& a_stream) override;			 // 18
		virtual void		  LinkObject(NiStream& a_stream) override;			 // 19 - { bhkSerializable::LinkObject(a_stream); }
		virtual bool		  RegisterStreamables(NiStream& a_stream) override;	 // 1A - { return bhkSerializable::RegisterStreamables(a_stream); }
		virtual void		  SaveBinary(NiStream& a_stream) override;			 // 1B
		virtual bool		  IsEqual(NiObject* a_object) override;				 // 1C
		virtual void		  Unk_26(void) override;							 // 26

		// add
		virtual void Unk_32(void);	// 32
		virtual void Unk_33(void);	// 33
		virtual void Unk_34(void);	// 34 - { return 0; }
		virtual void Unk_35(void);	// 35

		std::uint32_t GetMaterialID(hkpShapeKey a_key) const
		{
			using func_t = decltype(&bhkShape::GetMaterialID);
			REL::Relocation<func_t> func{ REL::ID(76799) };
			return func(this, a_key);
		}

		// members
		std::uint64_t unk20;  // 20
	};
	static_assert(sizeof(bhkShape) == 0x28);
}
