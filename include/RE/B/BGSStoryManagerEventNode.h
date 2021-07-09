#pragma once

#include "RE/B/BGSStoryManagerBranchNode.h"
#include "RE/B/BSString.h"
#include "RE/B/BSTArray.h"
#include "RE/F/FormTypes.h"

namespace RE
{
	struct BGSStoryEventMember
	{
		enum class DATA_TYPE
		{
		};

		stl::enumeration<DATA_TYPE, std::uint32_t> type;      // 00
		std::uint32_t                              uniqueID;  // 04
		BSString                                   name;      // 08
	};
	static_assert(sizeof(BGSStoryEventMember) == 0x18);

	struct BGSRegisteredStoryEvent  // ENAM
	{
		char                           uniqueID[4];  // 00
		std::uint32_t                  pad04;        // 04
		BSTArray<BGSStoryEventMember>* members;      // 08
		BSString                       name;         // 10
		bool                           immediate;    // 20
		std::uint8_t                   pad21;        // 21
		std::uint16_t                  pad22;        // 22
		std::uint32_t                  pad24;        // 24
	};
	static_assert(sizeof(BGSRegisteredStoryEvent) == 0x28);

	class BGSStoryManagerEventNode : public BGSStoryManagerBranchNode
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSStoryManagerEventNode;
		inline static constexpr auto FORMTYPE = FormType::StoryManagerEventNode;

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		~BGSStoryManagerEventNode() override;  // 00

		// override (BGSStoryManagerBranchNode)
		void        InitializeData() override;         // 04
		void        ClearData() override;              // 05 - { BGSStoryManagerNodeBase::ClearData(); }
		bool        Load(TESFile* a_mod) override;     // 06
		void        InitItemImpl() override;           // 13
		[[nodiscard]] const char* GetFormEditorID() const override;  // 32 - { if (!((flags >> 3) & 1)) return "(Uninitialized event node)"; return event ? event->name.c_str() : "(No event)"; }

		// members
		const BGSRegisteredStoryEvent* event;  // 60 - ENAM
	};
	static_assert(sizeof(BGSStoryManagerEventNode) == 0x68);
}
