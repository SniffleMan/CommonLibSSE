#pragma once

#include "RE/A/ActorValues.h"

namespace RE
{
	class ActorValueOwner
	{
	public:
		inline static constexpr auto RTTI = RTTI_ActorValueOwner;

		virtual ~ActorValueOwner();  // 00

		// add
		virtual float GetActorValue(ActorValue a_akValue);                                                      // 01 - { return 0.0; }
		virtual float GetPermanentActorValue(ActorValue a_akValue);                                             // 02 - { return 0.0; }
		virtual float GetBaseActorValue(ActorValue a_akValue);                                                  // 03 - { return 0.0; }
		virtual void  SetBaseActorValue(ActorValue a_akValue, float a_value);                                   // 04 - { return; }
		virtual void  ModActorValue(ActorValue a_akValue, float a_value);                                       // 05 - { return; }
		virtual void  RestoreActorValue(ACTOR_VALUE_MODIFIER a_modifier, ActorValue a_akValue, float a_value);  // 06 - { return; }
		virtual void  SetActorValue(ActorValue a_akValue, float a_value);                                       // 07 - { SetBaseActorValue(a_akValue, a_value); }
		[[nodiscard]] virtual bool  GetIsPlayerOwner() const;                                                                 // 08 - { return false; }

		[[nodiscard]] float GetArmorRatingSkillMultiplier(float a_skillLevel) const;
		[[nodiscard]] float GetClampedActorValue(ActorValue a_akValue) const;
	};
	static_assert(sizeof(ActorValueOwner) == 0x8);
}
