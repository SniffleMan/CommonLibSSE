#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTSmartPointer.h"

namespace RE
{
	class BSAnimationGraphManager;
	class BShkbAnimationGraph;
	class NiAVObject;

	class IAnimationGraphManagerHolder
	{
	public:
		inline static constexpr auto RTTI = RTTI_IAnimationGraphManagerHolder;

		virtual ~IAnimationGraphManagerHolder();  // 00

		// add
		virtual bool          NotifyAnimationGraph(const BSFixedString& a_eventName);                                                                              // 01
		virtual bool          GetAnimationGraphManagerImpl(BSTSmartPointer<BSAnimationGraphManager>& a_out) const = 0;                                             // 02
		virtual bool          SetAnimationGraphManagerImpl(BSTSmartPointer<BSAnimationGraphManager>& a_in) = 0;                                                    // 03
		virtual bool          PopulateGraphNodesToTarget(BSScrapArray<NiAVObject*>& a_nodes);                                                                      // 04 - { return false; }
		virtual bool          ConstructAnimationGraph(BSTSmartPointer<BShkbAnimationGraph>& a_out) = 0;                                                            // 05
		virtual void          Unk_06(void);                                                                                                                        // 06 - { return 1; }
		virtual void          Unk_07(void);                                                                                                                        // 07 - { return 1; }
		virtual bool          SetupAnimEventSinks(const BSTSmartPointer<BShkbAnimationGraph>& a_animGraph);                                                        // 08 - { return true; } - sinks the holder to the the source passed in
		virtual void          Unk_09(void);                                                                                                                        // 09 - { return; }
		virtual void          Unk_0A(void);                                                                                                                        // 0A - { return 0; }
		virtual void          PostCreateAnimationGraphManager(BSTSmartPointer<BSAnimationGraphManager>& a_animGraphMgr);                                           // 0B - { return; }
		virtual void          Unk_0C(void);                                                                                                                        // 0C - { return; }
		virtual void          PostChangeAnimationManager(const BSTSmartPointer<BShkbAnimationGraph>& a_arg1, const BSTSmartPointer<BShkbAnimationGraph>& a_arg2);  // 0D - { return; }
		virtual void          Unk_0E(void);                                                                                                                        // 0E - { return 1; }
		[[nodiscard]] virtual std::uint32_t GetGraphVariableCacheSize() const;                                                                                                   // 0F - { return 0; }
		virtual bool          GetGraphVariableImpl1(const BSFixedString& a_variableName, float& a_out) const;                                                      // 10
		virtual bool          GetGraphVariableImpl2(const BSFixedString& a_variableName, std::int32_t& a_out) const;                                               // 11
		virtual bool          GetGraphVariableImpl3(const BSFixedString& a_variableName, bool& a_out) const;                                                       // 12

		bool GetAnimationGraphManager(BSTSmartPointer<BSAnimationGraphManager>& a_out) const;
		bool GetGraphVariableFloat(const BSFixedString& a_variableName, float& a_out) const;
		bool GetGraphVariableInt(const BSFixedString& a_variableName, std::int32_t& a_out) const;
		bool GetGraphVariableBool(const BSFixedString& a_variableName, bool& a_out) const;
		bool SetAnimationGraphManager(BSTSmartPointer<BSAnimationGraphManager>& a_in);
	};
	static_assert(sizeof(IAnimationGraphManagerHolder) == 0x8);
}
