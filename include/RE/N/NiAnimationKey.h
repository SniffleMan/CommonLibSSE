#pragma once

namespace RE
{
	class NiAnimationKey
	{
	public:
		enum class KeyContent
		{
			kFloat,
			kPos,
			kRot,
			kColor,
			kText,
			kBool,

			kTotal
		};

		enum class KeyType
		{
			kNoInterp,
			kLink,
			kBez,
			kTCB,
			kEuler,
			kStrip,

			kTotal
		};

		NiAnimationKey();
		NiAnimationKey(float a_time);
		~NiAnimationKey();

		[[nodiscard]] float           GetTime() const;
		void            SetTime(float a_time);
		[[nodiscard]] NiAnimationKey* GetKeyAt(std::uint32_t a_index, std::uint8_t a_keySize) const;

	protected:
		// members
		float _time;  // 00
	};
	static_assert(sizeof(NiAnimationKey) == 0x4);
}
