#pragma once

#include "RE/G/GFxFileConstants.h"
#include "RE/G/GFxState.h"
#include "RE/G/GPtr.h"

namespace RE
{
	// StateBag collects accessor methods for properties that can be inherited from Loader to MovieDef and from MovieDef to Movie. These properties can be overwritten in any one of above mentioned instances.
	class GFxStateBag : public GFxFileConstants
	{
	protected:
		// add
		[[nodiscard]] virtual GFxStateBag* GetStateBagImpl() const;  // 00

	public:
		virtual ~GFxStateBag();  // 01

		virtual void      SetState(GFxState::StateType a_stateType, GFxState* a_state);                                                   // 02 - SetState sets an interface to State. The state type is passed to SetState so that we can know which state is being cleared when null is passed
		[[nodiscard]] virtual GFxState* GetStateAddRef(GFxState::StateType a_stateType) const;                                                          // 03 - GetStateAddRef obtains one or more State pointers based on the specified state type
		virtual void      GetStatesAddRef(GFxState** a_stateList, const GFxState::StateType* a_stateTypes, std::uint32_t a_count) const;  // 04 - GetStatesAddRef fills in a set of states with one call. Initial array a_stateList must contain null pointers

		template <class T>
		T* GetStateAddRef(GFxState::StateType a_state) const
		{
			return static_cast<T*>(GetStateAddRef(a_state));
		}

		[[nodiscard]] GPtr<GFxState> GetState(GFxState::StateType a_stateType) const;

		template <class T>
		GPtr<T> GetState(GFxState::StateType a_stateType) const
		{
			GPtr<T> ptr(GetStateAddRef<T>(a_stateType));
			ptr->Release();
			return ptr;
		}
	};
	static_assert(sizeof(GFxStateBag) == 0x8);
}
