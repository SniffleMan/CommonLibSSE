#pragma once

#include "RE/N/NiKeyBasedInterpolator.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class NiFloatData;

	class NiFloatInterpolator : public NiKeyBasedInterpolator
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiFloatInterpolator;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiFloatInterpolator;

		~NiFloatInterpolator() override;  // 00

		// override (NiKeyBasedInterpolator)
		const NiRTTI*   GetRTTI() const override;                                                               // 02
		NiObject*       CreateClone(NiCloningProcess& a_cloning) override;                                      // 17
		void            LoadBinary(NiStream& a_stream) override;                                                // 18
		void            LinkObject(NiStream& a_stream) override;                                                // 19 - { NiKeyBasedInterpolator::LinkObject(a_stream); }
		bool            RegisterStreamables(NiStream& a_stream) override;                                       // 1A
		void            SaveBinary(NiStream& a_stream) override;                                                // 1B
		bool            IsEqual(NiObject* a_object) override;                                                   // 1C
		bool            Update1(float a_time, NiObjectNET* a_interpTarget, NiQuatTransform& a_value) override;  // 25 - { return NiInterpolator::UpdateTransform(a_time, a_interpTarget, a_value); }
		bool            Update2(float a_time, NiObjectNET* a_target, NiColorA& a_value) override;               // 26 - { return NiInterpolator::UpdateTransform(a_time, a_interpTarget, a_value); }
		bool            Update3(float a_time, NiObjectNET* a_interpTarget, NiPoint3& a_value) override;         // 27 - { return NiInterpolator::UpdateTransform(a_time, a_interpTarget, a_value); }
		bool            Update4(float a_time, NiObjectNET* a_interpTarget, NiQuaternion& a_value) override;     // 28 - { return NiInterpolator::UpdateTransform(a_time, a_interpTarget, a_value); }
		bool            Update5(float a_time, NiObjectNET* a_interpTarget, float& a_value) override;            // 29
		bool            Update6(float a_time, NiObjectNET* a_interpTarget, bool& a_value) override;             // 2A - { return NiInterpolator::UpdateTransform(a_time, a_interpTarget, a_value); }
		bool            IsFloatValueSupported() const override;                                                 // 2C - { return true; }
		void            Collapse() override;                                                                    // 31
		void            GuaranteeTimeRange(float a_start, float a_end) override;                                // 33
		NiInterpolator* GetSequenceInterpolator(float a_start, float a_end) override;                           // 34
		std::uint16_t   GetKeyChannelCount() const override;                                                    // 39 - { return 1; }
		std::uint32_t   GetKeyCount(std::uint16_t a_channel) const override;                                    // 3A - { return floatData ? floatData->numKeys : 0; }
		KeyContent      GetKeyContent(std::uint16_t a_channel) const override;                                  // 3B - { KeyContent::kFloat; }
		KeyType         GetKeyType(std::uint16_t a_channel) const override;                                     // 3C - { return floatData ? floatData->type : 0; }
		void*           GetKeyArray(std::uint16_t a_channel) const override;                                    // 3D - { return floatData ? floatData->keys : 0; }
		std::uint8_t    GetKeyStride(std::uint16_t a_channel) const override;                                   // 3E - { return floatData ? floatData->keySize : 0; }
		[[nodiscard]] bool            GetChannelPosed(std::uint16_t a_channel) const override;                                // 3F - { return !floatData && floatValue != -3.4028235e38; }

		// members
		float                  floatValue;  // 18
		std::uint32_t          pad1C;       // 1C
		NiPointer<NiFloatData> floatData;   // 20
		std::uint32_t          lastIndex;   // 28
		std::uint32_t          pad2C;       // 2C
	};
	static_assert(sizeof(NiFloatInterpolator) == 0x30);
}
