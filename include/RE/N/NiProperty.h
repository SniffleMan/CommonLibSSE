#pragma once

#include "RE/N/NiObjectNET.h"

namespace RE
{
	class NiProperty : public NiObjectNET
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiProperty;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiProperty;

		enum class Type
		{
			kAlpha = 0,
			kShade = 1
		};

		~NiProperty() override;  // 00

		// override (NiObjectNET)
		const NiRTTI* GetRTTI() const override;                            // 02
		void          LoadBinary(NiStream& a_stream) override;             // 18 - { NiObjectNET::LoadBinary(a_stream); }
		void          LinkObject(NiStream& a_stream) override;             // 19 - { NiObjectNET::LinkObject(a_stream); }
		bool          RegisterStreamables(NiStream& a_stream) override;    // 1A - { return NiObjectNET::RegisterStreamables(a_stream); }
		void          SaveBinary(NiStream& a_stream) override;             // 1B - { NiObjectNET::SaveBinary(a_stream); }
		bool          IsEqual(NiObject* a_object) override;                // 1C - { return NiObjectNET::IsEqual(a_object); }
		void          ProcessClone(NiCloningProcess& a_cloning) override;  // 1D

		// add
		[[nodiscard]] virtual Type GetType() const = 0;   // 25
		virtual void Update(float a_time);  // 26
	};
	static_assert(sizeof(NiProperty) == 0x30);
}
