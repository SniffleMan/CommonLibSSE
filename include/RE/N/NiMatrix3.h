#pragma once

namespace RE
{
	class NiPoint3;

	class NiMatrix3
	{
	public:
		NiPoint3 operator*(const NiPoint3& a_rhs) const;

		void EulerAnglesToAxesZXY(const NiPoint3& a_angle);
		void EulerAnglesToAxesZXY(float a_xAngle, float a_yAngle, float a_zAngle);
		bool ToEulerAnglesXYZ(NiPoint3& a_angle) const;
		bool ToEulerAnglesXYZ(float& a_xAngle, float& a_yAngle, float& a_zAngle) const;

		// members
		float entry[3][3];	// 00
	};
	static_assert(sizeof(NiMatrix3) == 0x24);
}
