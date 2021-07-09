#pragma once

#include "RE/B/BSFixedString.h"

namespace RE
{
	class TESFile;
	class TESForm;
	class TESQuest;

	class BGSBaseAlias
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSBaseAlias;
		inline static constexpr auto VMTYPEID = static_cast<VMTypeID>(139);

		enum class FLAGS
		{
			kNone = 0,
			kReserves = 1 << 0,
			kOptional = 1 << 1,
			kQuestObject = 1 << 2,
			kAllowReuse = 1 << 3,
			kAllowDead = 1 << 4,
			kLoadedOnly = 1 << 5,
			kEssential = 1 << 6,
			kAllowDisabled = 1 << 7,
			kStoreName = 1 << 8,
			kAllowReserved = 1 << 9,
			kProtected = 1 << 10,
			kForcedFromAlias = 1 << 11,
			kAllowDestroyed = 1 << 12,
			kFindPlayerClosest = 1 << 13,
			kUsesNames = 1 << 14,
			kInitiallyDisabled = 1 << 15,
			kAllowCleared = 1 << 16,
			kClearNameOnRemove = 1 << 17,
			kActorsOnly = 1 << 18,
			kTransient = 1 << 19,
			kExternalLink = 1 << 20,
			kNoPickpocket = 1 << 21,
			kDataAlias = 1 << 22,
			kSceneOptional = 1 << 24,
			kCreateIn = 1 << 31  // BGSRefAlias
		};

		enum class FILL_TYPE  // BGSRefAlias
		{
			kConditions = 0,
			kForced = 1,
			kFromAlias = 2,
			kFromEvent = 3,
			kCreated = 4,
			kFromExternal = 5,
			kUniqueActor = 6,
			kNearAlias = 7
		};

		virtual ~BGSBaseAlias();  // 00

		// add
		virtual bool                 Load(TESFile* a_mod) = 0;       // 01
		virtual void                 InitItem(TESForm* a_form) = 0;  // 02
		[[nodiscard]] virtual const BSFixedString& QType() const = 0;              // 03

		[[nodiscard]] const BSFixedString& GetTypeString() const;
		[[nodiscard]] VMTypeID             GetVMTypeID() const;
		[[nodiscard]] bool                 IsQuestObject() const;

		// members
		BSFixedString                              aliasName;    // 08 - ALID
		TESQuest*                                  owningQuest;  // 10
		std::uint32_t                              aliasID;      // 18 - ALST/ALLS
		stl::enumeration<FLAGS, std::uint32_t>     flags;        // 1C - FNAM
		stl::enumeration<FILL_TYPE, std::uint16_t> fillType;     // 20
		std::uint16_t                              pad22;        // 22
		std::uint32_t                              pad24;        // 24
	};
	static_assert(sizeof(BGSBaseAlias) == 0x28);
}
