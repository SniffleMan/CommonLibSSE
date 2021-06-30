#pragma once

#include "RE/B/BGSBaseAlias.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/F/FormTypes.h"
#include "RE/Q/QuestEvents.h"

namespace RE
{
	class BGSLocationRefType;
	class TESBoundObject;
	class TESCondition;

	class BGSRefAlias : public BGSBaseAlias
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSRefAlias;
		inline static constexpr auto VMTYPEID = static_cast<VMTypeID>(140);

		struct ForcedFillData  // kForced
		{
		public:
			// members
			ObjectRefHandle forcedRef;  // 0 - ALFR
		};
		static_assert(sizeof(ForcedFillData) == 0x4);

		struct FromAliasFillData  // kFromAlias
		{
		public:
			// members
			std::uint32_t       forcedFromAlias;  // 00 - ALFA
			std::uint32_t       pad04;            // 04
			BGSLocationRefType* forcedRefType;    // 08 - ALRT
		};
		static_assert(sizeof(FromAliasFillData) == 0x10);

		struct FromEventFillData  // kFromEvent
		{
		public:
			// members
			QuestEvent    forcedFromEvent;  // ALFE
			std::uint32_t forcedEventData;  // ALFD
		};
		static_assert(sizeof(FromEventFillData) == 0x8);

		struct CreatedFillData  // kCreated
		{
		public:
			enum class Level  // ALCL
			{
				kEasy = 0,
				kMedium = 1,
				kHard = 2,
				kVeryHard = 3,
				kNone = 4
			};

			struct Alias  // ALCA
			{
			public:
				enum class Create
				{
					kAt = 0x0000,
					kIn = 0x8000
				};

				// members
				std::uint16_t                           alias;   // 0
				stl::enumeration<Create, std::uint16_t> create;  // 2
			};
			static_assert(sizeof(Alias) == 0x4);

			// members
			TESBoundObject*                        object;  // 00 - ALCO
			Alias                                  alias;   // 08 - ALCA
			stl::enumeration<Level, std::uint16_t> level;   // 0C - ALCL
			std::uint16_t                          pad0E;   // 0E
		};
		static_assert(sizeof(CreatedFillData) == 0x10);

		struct FromExternalFillData  // kFromExternal
		{
		public:
			// members
			TESQuest*     externalQuest;  // 00 - ALEQ
			std::uint32_t externalAlias;  // 08 - ALEA
			std::uint32_t pad0C;          // 0C
		};
		static_assert(sizeof(FromExternalFillData) == 0x10);

		struct UniqueActorFillData  // kUniqueActor
		{
		public:
			// members
			TESNPC* uniqueActor;  // 0 - ALUA
		};
		static_assert(sizeof(UniqueActorFillData) == 0x8);

		struct NearAliasFillData  // kNearAlias
		{
		public:
			enum class NEARFILLTYPE
			{
				kLinkedChildren = 0,
				kLinkedParents = 1
			};

			// members
			std::uint32_t                                 nearAlias;     // 0 - ALNA
			stl::enumeration<NEARFILLTYPE, std::uint32_t> nearFillType;  // 4 - ALNT
		};
		static_assert(sizeof(NearAliasFillData) == 0x8);

		union GenericFillData
		{
		public:
			struct Padding
			{
			public:
				// members
				std::uint64_t pad1;  // 00
				std::uint64_t pad2;  // 08
				std::uint64_t pad3;  // 10
			};
			static_assert(sizeof(Padding) == 0x18);

			~GenericFillData() {}

			// members
			Padding              padding;
			ForcedFillData       forced;
			FromAliasFillData    fromAlias;
			FromEventFillData    fromEvent;
			CreatedFillData      created;
			FromExternalFillData fromExternal;
			UniqueActorFillData  uniqueActor;
			NearAliasFillData    nearAlias;
		};
		static_assert(sizeof(GenericFillData) == 0x18);

		~BGSRefAlias() override;  // 00

		// override (BGSBaseAlias)
		bool                 Load(TESFile* a_mod) override;       // 01
		void                 InitItem(TESForm* a_form) override;  // 02
		[[nodiscard]] const BSFixedString& QType() const override;              // 03 - { return "Ref"; }

		// members
		GenericFillData fillData;    // 28
		TESCondition*   conditions;  // 40
	};
	static_assert(sizeof(BGSRefAlias) == 0x48);
}
