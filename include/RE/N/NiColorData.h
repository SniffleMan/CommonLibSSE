#pragma once

#include "RE/N/NiColorKey.h"
#include "RE/N/NiObject.h"

namespace RE
{
	class NiColorData : public NiObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiColorData;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiColorData;

		using KeyType = NiColorKey::KeyType;

		NiColorData();
		~NiColorData() override;  // 00

		// override (NiObject)
		const NiRTTI* GetRTTI() const override;                 // 02
		void          LoadBinary(NiStream& a_stream) override;  // 18
		void          SaveBinary(NiStream& a_stream) override;  // 1B
		bool          IsEqual(NiObject* a_object) override;     // 1C

		[[nodiscard]] std::uint32_t GetNumKeys() const;
		NiColorKey*   GetAnim(std::uint32_t& a_numKeys, NiColorKey::KeyType& a_type, std::uint8_t& a_size) const;

		// members
		std::uint32_t numKeys;  // 10
		std::uint32_t pad14;    // 14
		NiColorKey*   keys;     // 18
		KeyType       type;     // 20
		std::uint8_t  keySize;  // 24
		std::uint8_t  pad25;    // 25
		std::uint16_t pad26;    // 26
	};
	static_assert(sizeof(NiColorData) == 0x28);
}
