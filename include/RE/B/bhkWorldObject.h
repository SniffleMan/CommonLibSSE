#pragma once

#include "RE/B/bhkSerializable.h"

namespace RE
{
	class bhkWorldObject : public bhkSerializable
	{
	public:
		inline static constexpr auto RTTI = RTTI_bhkWorldObject;
		inline static constexpr auto Ni_RTTI = NiRTTI_bhkWorldObject;

		virtual ~bhkWorldObject();	// 00

		// override (bhkSerializable)
		virtual const NiRTTI* GetRTTI() const override;							 // 02
		virtual void		  LoadBinary(NiStream& a_stream) override;			 // 18
		virtual void		  LinkObject(NiStream& a_stream) override;			 // 19
		virtual bool		  RegisterStreamables(NiStream& a_stream) override;	 // 1A
		virtual void		  SaveBinary(NiStream& a_stream) override;			 // 1B
		virtual void		  Unk_26(void) override;							 // 26
		virtual hkpWorld*	  GetWorld() override;								 // 27 - { return world; }
		virtual void		  Unk_28(void) override;							 // 28 - { return world; }
		virtual void		  Unk_29(void) override;							 // 29

		// add
		virtual void Unk_32(void);	// 32 - { return Unk_29(); }

		void* GetPropertyValue(std::uint32_t a_key) const;
		template <class T>
		T* GetPropertyValue(std::uint32_t a_key) const
		{
			return static_cast<T*>(GetPropertyValue(a_key));
		}

		// members
		hkpWorld* world;  // 20
	};
	static_assert(sizeof(bhkWorldObject) == 0x28);
}
