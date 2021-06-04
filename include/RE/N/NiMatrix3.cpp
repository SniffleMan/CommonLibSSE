#include "RE/N/NiMatrix3.h"

#include "RE/N/NiMath.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	NiPoint3 NiMatrix3::operator*(const NiPoint3& a_rhs) const
	{
		return NiPoint3((entry[0][0] * a_rhs.x) + (entry[0][1] * a_rhs.y) + (entry[0][2] * a_rhs.z), (entry[1][0] * a_rhs.x) + (entry[1][1] * a_rhs.y) + (entry[1][2] * a_rhs.z), (entry[2][0] * a_rhs.x) + (entry[2][1] * a_rhs.y) + (entry[2][2] * a_rhs.z));
	}

	void NiMatrix3::EulerAnglesToAxesZXY(const NiPoint3& a_angle)
	{
		EulerAnglesToAxesZXY(a_angle.x, a_angle.y, a_angle.z);
	}

	void NiMatrix3::EulerAnglesToAxesZXY(float a_xAngle, float a_yAngle, float a_zAngle)
	{
		auto cosx = cos(a_xAngle);
		auto sinx = sin(a_xAngle);
		auto cosy = cos(a_yAngle);
		auto siny = sin(a_yAngle);
		auto cosz = cos(a_zAngle);
		auto sinz = sin(a_zAngle);

		entry[0][0] = cosz * cosy + sinz * sinx * siny;
		entry[0][1] = sinz * cosx;
		entry[0][2] = -cosz * siny + sinz * sinx * cosy;

		entry[1][0] = -sinz * cosy + cosz * sinx * siny;
		entry[1][1] = cosz * cosx;
		entry[1][2] = sinz * siny + cosz * sinx * cosy;

		entry[2][0] = cosx * siny;
		entry[2][1] = -sinx;
		entry[2][2] = cosx * cosy;
	}

	bool NiMatrix3::ToEulerAnglesXYZ(NiPoint3& a_angle) const
	{
		return ToEulerAnglesXYZ(a_angle.x, a_angle.y, a_angle.z);
	}

	bool NiMatrix3::ToEulerAnglesXYZ(float& a_xAngle, float& a_yAngle, float& a_zAngle) const
	{
		a_yAngle = -NiASin(entry[0][2]);
		if (a_yAngle < NI_HALF_PI) {
			if (a_yAngle > -NI_HALF_PI) {
				a_xAngle = -NiFastATan2(-entry[1][2], entry[2][2]);
				a_zAngle = -NiFastATan2(-entry[0][1], entry[0][0]);
				return true;
			} else {
				float rmY = NiFastATan2(entry[1][0], entry[1][1]);
				a_zAngle = 0.0;
				a_xAngle = rmY - a_zAngle;
				return false;
			}
		} else {
			float rpY = NiFastATan2(entry[1][0], entry[1][1]);
			a_zAngle = 0.0;
			a_xAngle = a_zAngle - rpY;
			return false;
		}
	}
}
