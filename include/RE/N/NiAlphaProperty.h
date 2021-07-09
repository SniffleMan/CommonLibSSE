#pragma once

#include "RE/N/NiProperty.h"

namespace RE
{
	class NiAlphaProperty : public NiProperty
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiAlphaProperty;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiAlphaProperty;

		enum class AlphaFunction
		{
			kOne = 0,
			kZero = 1,
			kSrcColor = 2,
			kInvSrcColor = 3,
			kDestColor = 4,
			kInvDestColor = 5,
			kSrcAlpha = 6,
			kInvSrcAlpha = 7,
			kDestAlpha = 8,
			kInvDestAlpha = 9,
			kSrcAlphaSat = 10
		};

		~NiAlphaProperty() override;  // 00

		// override (NiProperty)
		const NiRTTI* GetRTTI() const override;                           // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17
		void          LoadBinary(NiStream& a_stream) override;            // 18
		void          LinkObject(NiStream& a_stream) override;            // 19 - { NiProperty::LinkObject(a_stream); }
		bool          RegisterStreamables(NiStream& a_stream) override;   // 1A - { return NiProperty::RegisterStreamables(a_stream); }
		void          SaveBinary(NiStream& a_stream) override;            // 1B
		bool          IsEqual(NiObject* a_object) override;               // 1C
		[[nodiscard]] Type          GetType() const override;                           // 25 - { return Type::kAlpha; }

		// members
		std::uint64_t unk30;  // 30
	};
	static_assert(sizeof(NiAlphaProperty) == 0x38);
}
