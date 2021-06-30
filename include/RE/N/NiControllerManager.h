#pragma once

#include "RE/B/BSAnimNoteListener.h"
#include "RE/B/BSFixedString.h"
#include "RE/B/BSTHashMap.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/N/NiTArray.h"
#include "RE/N/NiTSet.h"
#include "RE/N/NiTimeController.h"

namespace RE
{
	class NiAVObjectPalette;
	class NiControllerSequence;

	class NiControllerManager : public NiTimeController
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiControllerManager;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiControllerManager;

		~NiControllerManager() override;  // 00

		// override (NiTimeController)
		const NiRTTI*        GetRTTI() const override;                            // 02
		NiObject*            CreateClone(NiCloningProcess& a_cloning) override;   // 17
		void                 LoadBinary(NiStream& a_stream) override;             // 18
		void                 LinkObject(NiStream& a_stream) override;             // 19
		bool                 RegisterStreamables(NiStream& a_stream) override;    // 1A
		void                 SaveBinary(NiStream& a_stream) override;             // 1B
		bool                 IsEqual(NiObject* a_object) override;                // 1C
		void                 ProcessClone(NiCloningProcess& a_cloning) override;  // 1D
		void                 PostLinkObject(NiStream& a_stream) override;         // 1E
		NiControllerManager* AsNiControllerManager() override;                    // 24 - { return this; }
		void                 Start(float a_time) override;                        // 25
		void                 Stop() override;                                     // 26
		void                 Update(float a_time) override;                       // 27
		void                 SetTarget(NiObjectNET* a_target) override;           // 28
		[[nodiscard]] bool                 TargetIsRequiredType() const override;               // 2E

		// add
		virtual void Start();  // 2F - { return; }

		NiControllerSequence* GetSequenceByName(std::string_view a_name);

		// members
		NiTObjectArray<NiPointer<NiControllerSequence>>  sequenceArray;    // 48
		NiTPrimitiveSet<NiControllerSequence*>           activeSequences;  // 60
		BSTHashMap<BSFixedString, NiControllerSequence*> stringMap;        // 70
		BSAnimNoteListener*                              listener;         // A0
		bool                                             cumulative;       // A8
		std::uint8_t                                     padA9;            // A9
		std::uint16_t                                    padAA;            // AA
		std::uint32_t                                    padAC;            // AC
		NiTObjectSet<NiPointer<NiControllerSequence>>    tempBlendSeqs;    // B0
		NiPointer<NiAVObjectPalette>                     objectPalette;    // C0
	};
	static_assert(sizeof(NiControllerManager) == 0xC8);
}
