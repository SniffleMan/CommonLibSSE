#pragma once

#include "RE/N/NiObject.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class NiObjectNET;

	NiSmartPointer(NiTimeController);

	class NiTimeController : public NiObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiTimeController;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiTimeController;

		enum class CycleType
		{
			kLoop,
			kReverse,
			kClamp,

			kTotal
		};

		enum class Flag
		{
			kAnimType_AppTime = 0 << 0,
			kAnimType_AppInit = 1 << 0,
			kAnimType_Mask = 1,

			kCycleType_Loop = 0 << 1,
			kCycleType_Reverse = 1 << 1,
			kCycleType_Clamp = 2 << 1,
			kCycleType_Mask = 6,

			kActive = 1 << 3,
			kPlayBackwards = 1 << 4,
			kManagerControlled = 1 << 5,
			kComputeScaledTime = 1 << 6,
			kForceUpdate = 1 << 7
		};

		inline NiTimeController() { ctor(); }
		~NiTimeController() override { dtor(); }  // 00

		// override (NiObject)
		const NiRTTI* GetRTTI() const override;                            // 02
		void          LoadBinary(NiStream& a_stream) override;             // 18
		void          LinkObject(NiStream& a_stream) override;             // 19
		bool          RegisterStreamables(NiStream& a_stream) override;    // 1A
		void          SaveBinary(NiStream& a_stream) override;             // 1B
		bool          IsEqual(NiObject* a_object) override;                // 1C
		void          ProcessClone(NiCloningProcess& a_cloning) override;  // 1D

		// add
		virtual void  Start(float a_time);                             // 25
		virtual void  Stop();                                          // 26
		virtual void  Update(float a_time) = 0;                        // 27
		virtual void  SetTarget(NiObjectNET* a_target);                // 28
		[[nodiscard]] virtual bool  IsTransformController() const { return false; }  // 29
		[[nodiscard]] virtual bool  IsVertexController() const { return false; }     // 2A
		virtual float ComputeScaledTime(float a_time);                 // 2B
		virtual void  OnPreDisplay() { return; }                       // 2C
		[[nodiscard]] virtual bool  IsStreamable() const { return true; }            // 2D
		[[nodiscard]] virtual bool  TargetIsRequiredType() const = 0;                // 2E

		[[nodiscard]] constexpr NiTimeController* GetNext() const noexcept { return next.get(); }

		// members
		stl::enumeration<Flag, std::uint16_t> flags;             // 10
		std::uint16_t                         pad12;             // 12
		float                                 frequency;         // 14
		float                                 phase;             // 18
		float                                 loKeyTime;         // 1C
		float                                 hiKeyTime;         // 20
		float                                 startTime;         // 24
		float                                 lastTime;          // 28
		float                                 weightedLastTime;  // 2C
		float                                 scaledTime;        // 30
		std::uint32_t                         pad34;             // 34
		NiObjectNET*                          target;            // 38
		NiPointer<NiTimeController>           next;              // 40 - singly-linked list

	private:
		NiTimeController* ctor();
		void              dtor();
	};
	static_assert(sizeof(NiTimeController) == 0x48);
}
