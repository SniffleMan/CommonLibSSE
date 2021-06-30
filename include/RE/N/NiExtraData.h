#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/N/NiObject.h"

namespace RE
{
	class NiExtraData : public NiObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiExtraData;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiExtraData;

		~NiExtraData() override;  // 00

		// override (NiObject)
		const NiRTTI* GetRTTI() const override;                          // 02
		void          LoadBinary(NiStream& a_stream) override;           // 18
		void          LinkObject(NiStream& a_stream) override;           // 19 - { return; }
		bool          RegisterStreamables(NiStream& a_stream) override;  // 1A
		void          SaveBinary(NiStream& a_stream) override;           // 1B
		bool          IsEqual(NiObject* a_object) override;              // 1C

		// add
		[[nodiscard]] virtual bool IsStreamable() const;  // 25 - { return true; }
		[[nodiscard]] virtual bool IsCloneable() const;   // 26 - { return true; }

		static NiExtraData* Create(std::size_t a_size, std::uintptr_t a_vtbl);

		[[nodiscard]] const BSFixedString& GetName() const;
		void                 SetName(const BSFixedString& a_name);

		// members
		BSFixedString name;  // 10
	};
	static_assert(sizeof(NiExtraData) == 0x18);
}
