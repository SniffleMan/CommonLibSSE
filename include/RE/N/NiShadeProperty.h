#pragma once

#include "RE/N/NiProperty.h"

namespace RE
{
	class NiShadeProperty : public NiProperty
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiShadeProperty;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiShadeProperty;

		~NiShadeProperty() override;  // 00

		// override (NiProperty)
		const NiRTTI* GetRTTI() const override;                           // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17
		void          LoadBinary(NiStream& a_stream) override;            // 18 - { NiProperty::LoadBinary(a_stream); }
		void          LinkObject(NiStream& a_stream) override;            // 19 - { NiProperty::LinkObject(a_stream); }
		bool          RegisterStreamables(NiStream& a_stream) override;   // 1A - { return NiProperty::RegisterStreamables(a_stream); }
		void          SaveBinary(NiStream& a_stream) override;            // 1B - { NiProperty::SaveBinary(a_stream); }
		bool          IsEqual(NiObject* a_object) override;               // 1C - { return NiProperty::IsEqual(a_object); }
		[[nodiscard]] Type          GetType() const override;                           // 25 - { return Type::kShade; }

		// add
		virtual void Unk_27(void);  // 27 - { return 1; }
		virtual void Unk_28(void);  // 28 - { return 1; }
		virtual void Unk_29(void);  // 29 - { return; }
	};
	static_assert(sizeof(NiShadeProperty) == 0x30);
}
