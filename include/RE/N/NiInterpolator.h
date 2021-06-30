#pragma once

#include "RE/N/NiObject.h"

namespace RE
{
	class NiAVObjectPalette;
	class NiBoolInterpolator;
	class NiColorA;
	class NiObjectNET;
	class NiPoint3;
	class NiQuaternion;
	class NiQuatTransform;

	class NiInterpolator : public NiObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiInterpolator;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiInterpolator;

		~NiInterpolator() override;  // 00

		// override (NiObject)
		const NiRTTI* GetRTTI() const override;                          // 02
		void          LoadBinary(NiStream& a_stream) override;           // 18 - { NiObject::LoadBinary(a_stream); }
		void          LinkObject(NiStream& a_stream) override;           // 19 - { NiObject::LinkObject(a_stream); }
		bool          RegisterStreamables(NiStream& a_stream) override;  // 1A - { return NiObject::RegisterStreamables(a_stream); }
		void          SaveBinary(NiStream& a_stream) override;           // 1B - { NiObject::SaveBinary(a_stream); }
		bool          IsEqual(NiObject* a_object) override;              // 1C - { return NiObject::IsEqual(a_stream); }

		// add
		virtual bool                Update1(float a_time, NiObjectNET* a_interpTarget, NiQuatTransform& a_value);  // 25 - { return false; }
		virtual bool                Update2(float a_time, NiObjectNET* a_interpTarget, NiColorA& a_value);         // 26 - { return false; }
		virtual bool                Update3(float a_time, NiObjectNET* a_interpTarget, NiPoint3& a_value);         // 27 - { return false; }
		virtual bool                Update4(float a_time, NiObjectNET* a_interpTarget, NiQuaternion& a_value);     // 28 - { return false; }
		virtual bool                Update5(float a_time, NiObjectNET* a_interpTarget, float& a_value);            // 29 - { return false; }
		virtual bool                Update6(float a_time, NiObjectNET* a_interpTarget, bool& a_value);             // 2A - { return false; }
		[[nodiscard]] virtual bool                IsBoolValueSupported() const;                                                  // 2B - { return false; }
		[[nodiscard]] virtual bool                IsFloatValueSupported() const;                                                 // 2C - { return false; }
		[[nodiscard]] virtual bool                IsQuaternionValueSupported() const;                                            // 2D - { return false; }
		[[nodiscard]] virtual bool                IsPoint3ValueSupported() const;                                                // 2E - { return false; }
		[[nodiscard]] virtual bool                IsColorAValueSupported() const;                                                // 2F - { return false; }
		[[nodiscard]] virtual bool                IsTransformValueSupported() const;                                             // 30 - { return false; }
		virtual void                Collapse();                                                                    // 31 - { return; }
		virtual void                GetActiveTimeRange(float& a_beginKeyTime, float& a_endKeyTime) const;          // 32 - { a_beginKeyTime = 0.0; a_endKeyTime = 0.0; }
		virtual void                GuaranteeTimeRange(float a_startTime, float a_endTime);                        // 33 - { return; }
		virtual NiInterpolator*     GetSequenceInterpolator(float a_startTime, float a_endTime);                   // 34
		virtual bool                ResolveDependencies(NiAVObjectPalette* a_palette);                             // 35 - { return true; }
		virtual bool                SetUpDependencies();                                                           // 36 - { return true; }
		[[nodiscard]] virtual bool                AlwaysUpdate() const;                                                          // 37 - { return false; }
		virtual NiBoolInterpolator* AsNiBoolInterpolator();                                                        // 38 - { return 0; }

		bool Update(float a_time, NiObjectNET* a_interpTarget, NiQuatTransform& a_value);
		bool Update(float a_time, NiObjectNET* a_interpTarget, NiColorA& a_value);
		bool Update(float a_time, NiObjectNET* a_interpTarget, NiPoint3& a_value);
		bool Update(float a_time, NiObjectNET* a_interpTarget, NiQuaternion& a_value);
		bool Update(float a_time, NiObjectNET* a_interpTarget, float& a_value);
		bool Update(float a_time, NiObjectNET* a_interpTarget, bool& a_value);

		// members
		float         lastTime;  // 10
		std::uint32_t pad14;     // 14
	};
	static_assert(sizeof(NiInterpolator) == 0x18);
}
