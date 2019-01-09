#pragma once

#include "RE/BGSDestructibleObjectForm.h"  // BGSDestructibleObjectForm
#include "RE/BGSPickupPutdownSounds.h"  // BGSPickupPutdownSounds
#include "RE/SpellItem.h"  // SpellItem
#include "RE/TESModelTextureSwap.h"  // TESModelTextureSwap
#include "RE/TESValueForm.h"  // TESValueForm
#include "RE/TESWeightForm.h"  // TESWeightForm


namespace RE
{
	class ScrollItem :
		public SpellItem,					// 000
		public TESModelTextureSwap,			// 0E8
		public BGSDestructibleObjectForm,	// 120
		public BGSPickupPutdownSounds,		// 130
		public TESWeightForm,				// 148
		public TESValueForm					// 158
	{
	public:
		virtual ~ScrollItem();									// 00

		// override (SpellItem)
		virtual void		InitItem() override;				// 13
		virtual MagicType	GetMagicType() const override;		// 53 - { return MagicType::kScroll; }
		virtual CastType	GetCastType() const override;		// 55 - { return CastType::kFireAndForget; }
		virtual ActorValue	GetActorValueType() const override;	// 66 - { return ActorValue::kNone; }
	};
	STATIC_ASSERT(sizeof(ScrollItem) == 0x168);
}