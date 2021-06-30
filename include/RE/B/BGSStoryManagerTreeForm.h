#pragma once

#include "RE/B/BSTArray.h"
#include "RE/F/FormTypes.h"
#include "RE/T/TESForm.h"

namespace RE
{
	class BGSStoryManagerBranchNode;
	class BGSStoryManagerQuestNode;
	class BGSStoryManagerTreeForm;
	class PeriodicUpdateTimer;
	class TESCondition;

	class BGSStoryManagerTreeVisitor
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSStoryManagerTreeVisitor;

		enum class VisitControl
		{
		};

		virtual ~BGSStoryManagerTreeVisitor();  // 00

		// add
		virtual VisitControl VisitBranchNode(BGSStoryManagerBranchNode& a_node);             // 01
		virtual VisitControl VisitQuestNode(BGSStoryManagerQuestNode& a_node, bool a_arg2);  // 02
		virtual VisitControl VisitQuest(TESQuest& a_quest);                                  // 03
		virtual void         Revert();                                                       // 04

		// members
		PeriodicUpdateTimer*               timer;               // 08
		std::int32_t                       currentCursorDepth;  // 10
		std::uint32_t                      pad14;               // 14
		BGSStoryManagerQuestNode*          lastQuestParent;     // 18
		BSTArray<BGSStoryManagerTreeForm*> cursorAncestry;      // 20
		std::uint32_t                      queryID;             // 38
		std::uint32_t                      pad3C;               // 3C
	};
	static_assert(sizeof(BGSStoryManagerTreeVisitor) == 0x40);

	class BGSStoryManagerTreeForm : public TESForm
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSStoryManagerTreeForm;

		~BGSStoryManagerTreeForm() override;  // 00

		// add
		[[nodiscard]] virtual std::uint32_t                            QChildCount() const;                                       // 3B - { return 0; }
		[[nodiscard]] virtual BGSStoryManagerTreeForm*                 GetChild(std::uint32_t a_idx) const;                       // 3C - { return 0; }
		virtual TESCondition*                            QConditions() = 0;                                         // 3D
		virtual BGSStoryManagerTreeVisitor::VisitControl AcceptVisitor(BGSStoryManagerTreeVisitor& a_visitor) = 0;  // 3E

		// members
		std::uint32_t lastVisitorID;  // 20
		std::uint32_t pad24;          // 24
	};
	static_assert(sizeof(BGSStoryManagerTreeForm) == 0x28);
}
