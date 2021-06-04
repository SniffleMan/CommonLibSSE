#pragma once

#include "RE/B/BSTEvent.h"
#include "RE/B/BSTList.h"
#include "RE/B/BSTTuple.h"
#include "RE/I/ICellAttachDetachEventSource.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	namespace BSResource
	{
		struct ArchiveStreamOpenedEvent;
	}

	class BSSystemEvent;
	class BSTempNodeManager;
	class GridCellArray;
	class ImageSpaceModifierInstance;
	class NiNode;
	class NiPoint3;
	class Sky;
	class TESActorBase;
	class TESObjectCELL;
	class TESWorldSpace;

	struct PositionPlayerEvent;

	class TES :
		public ICellAttachDetachEventSource,						// 000
		public BSTEventSink<BSResource::ArchiveStreamOpenedEvent>,	// 060
		public BSTEventSink<PositionPlayerEvent>					// 068
	{
	public:
		inline static constexpr auto RTTI = RTTI_TES;

		class SystemEventAdapter : public BSTEventSink<BSSystemEvent>
		{
		public:
			inline static constexpr auto RTTI = RTTI_TES;

			virtual ~SystemEventAdapter();	// 00

			// override (BSTEventSink<BSSystemEvent>)
			virtual BSEventNotifyControl ProcessEvent(const BSSystemEvent* a_event, BSTEventSource<BSSystemEvent>* a_eventSource) override;	 // 01

			// members
			std::uint64_t unk08;  // 08
		};
		static_assert(sizeof(SystemEventAdapter) == 0x10);

		virtual ~TES();	 // 00

		// override (BSTEventSink<BSResource::ArchiveStreamOpenedEvent>)
		virtual BSEventNotifyControl ProcessEvent(const BSResource::ArchiveStreamOpenedEvent* a_event, BSTEventSource<BSResource::ArchiveStreamOpenedEvent>* a_eventSource) override;  // 01 - { return BSEventNotifyControl::kContinue; }

		// override (BSTEventSink<PositionPlayerEvent>)
		virtual BSEventNotifyControl ProcessEvent(const PositionPlayerEvent* a_event, BSTEventSource<PositionPlayerEvent>* a_eventSource) override;	 // 01

		static TES* GetSingleton();

		TESObjectCELL* GetCell(NiPoint3* a_position) const
		{
			using func_t = decltype(&TES::GetCell);
			REL::Relocation<func_t> func{ REL::ID(13177) };
			return func(this, a_position);
		}

		std::uint32_t GetMaterialID(NiPoint3* a_position) const
		{
			using func_t = decltype(&TES::GetMaterialID);
			REL::Relocation<func_t> func{ REL::ID(13203) };
			return func(this, a_position);
		}

		// members
		std::uint64_t										  unk070;					  // 070
		GridCellArray*										  gridCells;				  // 078
		NiNode*												  objRoot;					  // 080
		NiNode*												  lodLandRoot;				  // 088
		NiNode*												  objLODWaterRoot;			  // 090
		BSTempNodeManager*									  tempNodeManager;			  // 098
		std::uint64_t										  unk0A0;					  // 0A0
		std::uint64_t										  unk0A8;					  // 0A8
		std::uint64_t										  unk0B0;					  // 0B0
		std::uint64_t										  unk0B8;					  // 0B8
		TESObjectCELL*										  interiorCell;				  // 0C0
		TESObjectCELL**										  interiorBuffer;			  // 0C8
		void*												  unk0D0;					  // 0D0
		std::uint64_t										  unk0D8;					  // 0D8
		std::uint64_t										  unk0E0;					  // 0E0
		std::uint64_t										  unk0E8;					  // 0E8
		std::uint64_t										  unk0F0;					  // 0F0
		std::uint64_t										  unk0F8;					  // 0F8
		Sky*												  sky;						  // 100
		BSSimpleList<NiPointer<ImageSpaceModifierInstance>>	  activeImageSpaceModifiers;  // 108
		std::uint64_t										  unk118;					  // 118
		std::uint64_t										  unk120;					  // 120
		std::uint8_t										  unk128;					  // 128
		bool												  showLANDborders;			  // 129
		std::uint8_t										  unk12A;					  // 12A
		std::uint8_t										  unk12B;					  // 12B
		std::uint8_t										  unk12C;					  // 12C
		std::uint8_t										  unk12D;					  // 12D
		std::uint8_t										  unk12E;					  // 12E
		std::uint8_t										  unk12F;					  // 12F
		std::uint16_t										  unk130;					  // 130
		std::uint8_t										  unk132;					  // 132
		std::uint8_t										  unk133;					  // 133
		std::uint32_t										  unk134;					  // 134
		std::uint64_t										  unk138;					  // 138
		TESWorldSpace*										  worldSpace;				  // 140
		BSSimpleList<BSTTuple<TESActorBase*, std::uint16_t>*> deadCount;				  // 148
		void*												  unk158;					  // 158 - smart ptr
		void*												  unk160;					  // 160 - smart ptr
		void*												  unk168;					  // 168 - smart ptr
		void*												  unk170;					  // 170 - smart ptr
		std::uint64_t										  unk178;					  // 178
		std::uint64_t										  unk180;					  // 180
		std::uint64_t										  unk188;					  // 188
		std::uint64_t										  unk190;					  // 190
		std::uint64_t										  unk198;					  // 198
		std::uint64_t										  unk1A0;					  // 1A0
		std::uint64_t										  unk1A8;					  // 1A8
		std::uint64_t										  unk1B0;					  // 1B0
		std::uint64_t										  unk1B8;					  // 1B8
		std::uint64_t										  unk1C0;					  // 1C0
		std::uint64_t										  unk1C8;					  // 1C8
		std::uint64_t										  unk1D0;					  // 1D0
		std::uint64_t										  unk1D8;					  // 1D8
		std::uint64_t										  unk1E0;					  // 1E0
		std::uint64_t										  unk1E8;					  // 1E8
		std::uint64_t										  unk1F0;					  // 1F0
		std::uint64_t										  unk1F8;					  // 1F8
		std::uint64_t										  unk200;					  // 200
		std::uint64_t										  unk208;					  // 208
		std::uint64_t										  unk210;					  // 210
		std::uint64_t										  unk218;					  // 218
		std::uint64_t										  unk220;					  // 220
		std::uint64_t										  unk228;					  // 228
		std::uint64_t										  unk230;					  // 230
		std::uint64_t										  unk238;					  // 238
		std::uint64_t										  unk240;					  // 240
		std::uint64_t										  unk248;					  // 248
		std::uint64_t										  unk250;					  // 250
		std::uint64_t										  unk258;					  // 258
		std::uint64_t										  unk260;					  // 260
		std::uint64_t										  unk268;					  // 268
		std::uint64_t										  unk270;					  // 270
		std::uint64_t										  unk278;					  // 278
		std::uint64_t										  unk280;					  // 280
		std::uint64_t										  unk288;					  // 288
		SystemEventAdapter									  unk290;					  // 290
		std::uint64_t										  unk2A0;					  // 2A0
		std::uint64_t										  unk2A8;					  // 2A8
		std::uint64_t										  unk2B0;					  // 2B0
	};
	static_assert(sizeof(TES) == 0x2B8);
}
