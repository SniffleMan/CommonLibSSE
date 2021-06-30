#pragma once

namespace RE
{
	class BSISoundCategory
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSISoundCategory;

		virtual ~BSISoundCategory();  // 00

		// add
		virtual bool          Matches(const BSISoundCategory* a_category) const = 0;  // 01
		[[nodiscard]] virtual float         GetCategoryVolume() const = 0;                          // 02
		virtual void          SetCategoryVolume(float a_value) = 0;                   // 03
		[[nodiscard]] virtual float         GetCategoryFrequency() const = 0;                       // 04
		virtual void          SetCategoryFrequency(float a_value) = 0;                // 05
		[[nodiscard]] virtual std::uint16_t GetCategoryAttenuation() const = 0;                     // 06
		virtual void          SetCategoryAttenuation(std::uint16_t a_value) = 0;      // 07
		virtual void          Unk_08(void) = 0;                                       // 08
		virtual void          Unk_09(void) = 0;                                       // 09
		virtual void          Unk_0A(void) = 0;                                       // 0A
		virtual void          Unk_0B(void) = 0;                                       // 0B
	};
	static_assert(sizeof(BSISoundCategory) == 0x8);
}
