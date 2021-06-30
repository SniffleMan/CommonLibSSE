#pragma once

namespace RE
{
	using hkObjectIndex = std::uint16_t;
	using hkTime = float;

	enum class hkResult
	{
		kSuccess = 0,
		kFailure = 1
	};

	// 16-bit float with 7-bit precision
	class hkHalf
	{
	public:
		hkHalf();
		explicit hkHalf(const float& a_val);

		hkHalf& operator=(const float& a_val);
				operator float() const;

	protected:
		void  SetFloat(const float& a_val);
		[[nodiscard]] float GetFloat() const;

		// members
		std::int16_t _value;  // 0
	};
	static_assert(sizeof(hkHalf) == 0x2);

	// 8-bit float ranging [0.01, 1000000.0]
	// value is an index in a lookup table
	class hkUFloat8
	{
	public:
		// members
		std::uint8_t value;  // 0
	};
	static_assert(sizeof(hkUFloat8) == 0x1);
}
