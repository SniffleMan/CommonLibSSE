#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/F/FormTypes.h"
#include "RE/N/NiRefObject.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	struct AttackData  // ATKD
	{
	public:
		enum class AttackFlag
		{
			kNone = 0,
			kIgnoreWeapon = 1 << 0,
			kBashAttack = 1 << 1,
			kPowerAttack = 1 << 2,
			kChargeAttack = 1 << 3,
			kRotatingAttack = 1 << 4,
			kContinuousAttack = 1 << 5,
			kOverrideData = 1 << 31
		};

		// members
		float                                       damageMult;     // 00
		float                                       attackChance;   // 04
		SpellItem*                                  attackSpell;    // 08
		stl::enumeration<AttackFlag, std::uint32_t> flags;          // 10
		float                                       attackAngle;    // 14
		float                                       strikeAngle;    // 18
		float                                       staggerOffset;  // 1C
		BGSKeyword*                                 attackType;     // 20
		float                                       knockDown;      // 28
		float                                       recoveryTime;   // 2C
		float                                       staminaMult;    // 30
		std::uint32_t                               pad34;          // 34
	};
	static_assert(sizeof(AttackData) == 0x38);

	NiSmartPointer(BGSAttackData);

	class BGSAttackData : public NiRefObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSAttackData;

		~BGSAttackData() override;  // 00

		[[nodiscard]] bool IsLeftAttack() const;

		// members
		BSFixedString event;  // 10 - ATKE
		AttackData    data;   // 18 - ATKD
	};
	static_assert(sizeof(BGSAttackData) == 0x50);
}
