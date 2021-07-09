#pragma once

namespace RE
{
	class NiPoint3
	{
	public:
		constexpr NiPoint3() noexcept = default;

		constexpr NiPoint3(float a_x, float a_y, float a_z) noexcept :
			x(a_x),
			y(a_y),
			z(a_z){};

		float&       operator[](std::size_t a_idx);
		const float& operator[](std::size_t a_idx) const;
		bool         operator==(const NiPoint3& a_rhs) const;
		bool         operator!=(const NiPoint3& a_rhs) const;
		NiPoint3     operator+(const NiPoint3& a_rhs) const;
		NiPoint3     operator-(const NiPoint3& a_rhs) const;
		float        operator*(const NiPoint3& a_rhs) const;
		NiPoint3     operator*(float a_scalar) const;
		NiPoint3     operator/(float a_scalar) const;
		NiPoint3     operator-() const;
		NiPoint3&    operator+=(const NiPoint3& a_rhs);
		NiPoint3&    operator-=(const NiPoint3& a_rhs);
		NiPoint3&    operator*=(float a_scalar);
		NiPoint3&    operator/=(float a_scalar);

		[[nodiscard]] NiPoint3            Cross(const NiPoint3& pt) const;
		[[nodiscard]] float GetDistance(const NiPoint3& a_pt) const noexcept;
		[[nodiscard]] float GetSquaredDistance(const NiPoint3& a_pt) const noexcept;
		[[nodiscard]] float               Length() const;
		[[nodiscard]] float               SqrLength() const;
		[[nodiscard]] NiPoint3            UnitCross(const NiPoint3& a_pt) const;
		float               Unitize();

		// members
		float x{ 0.0F };  // 0
		float y{ 0.0F };  // 4
		float z{ 0.0F };  // 8
	};
	static_assert(sizeof(NiPoint3) == 0xC);
}
