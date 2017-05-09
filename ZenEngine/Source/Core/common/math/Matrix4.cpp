// // /**
// //  * Matrix4.cpp
// //  * Dylan Bailey
// //  * 20170507
// // */
#include "stdafx.h"
#include "Source/Core/common/math/Matrix4.hpp"

namespace Zen
{
	void Matrix4::InitScaleTransform(float ScaleX, float ScaleY, float ScaleZ) {
		m[0][0] = ScaleX;
		m[0][1] = 0.0f;
		m[0][2] = 0.0f;
		m[0][3] = 0.0f;
		m[1][0] = 0.0f;
		m[1][1] = ScaleY;
		m[1][2] = 0.0f;
		m[1][3] = 0.0f;
		m[2][0] = 0.0f;
		m[2][1] = 0.0f;
		m[2][2] = ScaleZ;
		m[2][3] = 0.0f;
		m[3][0] = 0.0f;
		m[3][1] = 0.0f;
		m[3][2] = 0.0f;
		m[3][3] = 1.0f;
	}

	void Matrix4::InitRotateTransform(float RotateX, float RotateY, float RotateZ) {
		Matrix4 rx, ry, rz;

		const float x = ToRadian(RotateX);
		const float y = ToRadian(RotateY);
		const float z = ToRadian(RotateZ);

		rx.m[0][0] = 1.0f;
		rx.m[0][1] = 0.0f;
		rx.m[0][2] = 0.0f;
		rx.m[0][3] = 0.0f;
		rx.m[1][0] = 0.0f;
		rx.m[1][1] = cosf(x);
		rx.m[1][2] = -sinf(x);
		rx.m[1][3] = 0.0f;
		rx.m[2][0] = 0.0f;
		rx.m[2][1] = sinf(x);
		rx.m[2][2] = cosf(x);
		rx.m[2][3] = 0.0f;
		rx.m[3][0] = 0.0f;
		rx.m[3][1] = 0.0f;
		rx.m[3][2] = 0.0f;
		rx.m[3][3] = 1.0f;

		ry.m[0][0] = cosf(y);
		ry.m[0][1] = 0.0f;
		ry.m[0][2] = -sinf(y);
		ry.m[0][3] = 0.0f;
		ry.m[1][0] = 0.0f;
		ry.m[1][1] = 1.0f;
		ry.m[1][2] = 0.0f;
		ry.m[1][3] = 0.0f;
		ry.m[2][0] = sinf(y);
		ry.m[2][1] = 0.0f;
		ry.m[2][2] = cosf(y);
		ry.m[2][3] = 0.0f;
		ry.m[3][0] = 0.0f;
		ry.m[3][1] = 0.0f;
		ry.m[3][2] = 0.0f;
		ry.m[3][3] = 1.0f;

		rz.m[0][0] = cosf(z);
		rz.m[0][1] = -sinf(z);
		rz.m[0][2] = 0.0f;
		rz.m[0][3] = 0.0f;
		rz.m[1][0] = sinf(z);
		rz.m[1][1] = cosf(z);
		rz.m[1][2] = 0.0f;
		rz.m[1][3] = 0.0f;
		rz.m[2][0] = 0.0f;
		rz.m[2][1] = 0.0f;
		rz.m[2][2] = 1.0f;
		rz.m[2][3] = 0.0f;
		rz.m[3][0] = 0.0f;
		rz.m[3][1] = 0.0f;
		rz.m[3][2] = 0.0f;
		rz.m[3][3] = 1.0f;

		*this = rz * ry * rx;
	}

	void Matrix4::InitRotateTransform(const Quaternion& quat) {
		float yy2 = 2.0f * quat.y * quat.y;
		float xy2 = 2.0f * quat.x * quat.y;
		float xz2 = 2.0f * quat.x * quat.z;
		float yz2 = 2.0f * quat.y * quat.z;
		float zz2 = 2.0f * quat.z * quat.z;
		float wz2 = 2.0f * quat.w * quat.z;
		float wy2 = 2.0f * quat.w * quat.y;
		float wx2 = 2.0f * quat.w * quat.x;
		float xx2 = 2.0f * quat.x * quat.x;
		m[0][0] = -yy2 - zz2 + 1.0f;
		m[0][1] = xy2 + wz2;
		m[0][2] = xz2 - wy2;
		m[0][3] = 0;
		m[1][0] = xy2 - wz2;
		m[1][1] = -xx2 - zz2 + 1.0f;
		m[1][2] = yz2 + wx2;
		m[1][3] = 0;
		m[2][0] = xz2 + wy2;
		m[2][1] = yz2 - wx2;
		m[2][2] = -xx2 - yy2 + 1.0f;
		m[2][3] = 0.0f;
		m[3][0] = m[3][1] = m[3][2] = 0;
		m[3][3] = 1.0f;
	}

	void Matrix4::InitTranslationTransform(float x, float y, float z) {
		m[0][0] = 1.0f;
		m[0][1] = 0.0f;
		m[0][2] = 0.0f;
		m[0][3] = x;
		m[1][0] = 0.0f;
		m[1][1] = 1.0f;
		m[1][2] = 0.0f;
		m[1][3] = y;
		m[2][0] = 0.0f;
		m[2][1] = 0.0f;
		m[2][2] = 1.0f;
		m[2][3] = z;
		m[3][0] = 0.0f;
		m[3][1] = 0.0f;
		m[3][2] = 0.0f;
		m[3][3] = 1.0f;
	}

	void Matrix4::InitCameraTransform(const Vector3& Target, const Vector3& Up) {
		Vector3 N = Target;
		N.Normalize();
		Vector3 U = Up;
		U = U.Cross(N);
		U.Normalize();
		Vector3 V = N.Cross(U);

		m[0][0] = U.x;
		m[0][1] = U.y;
		m[0][2] = U.z;
		m[0][3] = 0.0f;
		m[1][0] = V.x;
		m[1][1] = V.y;
		m[1][2] = V.z;
		m[1][3] = 0.0f;
		m[2][0] = N.x;
		m[2][1] = N.y;
		m[2][2] = N.z;
		m[2][3] = 0.0f;
		m[3][0] = 0.0f;
		m[3][1] = 0.0f;
		m[3][2] = 0.0f;
		m[3][3] = 1.0f;
	}

	void Matrix4::InitPersProjTransform(const PersProjInfo& p) {
		const float ar = p.Width / p.Height;
		const float zRange = p.zNear - p.zFar;
		const float tanHalfFOV = tanf(ToRadian(p.FOV / 2.0f));

		m[0][0] = 1.0f / (tanHalfFOV * ar);
		m[0][1] = 0.0f;
		m[0][2] = 0.0f;
		m[0][3] = 0.0;
		m[1][0] = 0.0f;
		m[1][1] = 1.0f / tanHalfFOV;
		m[1][2] = 0.0f;
		m[1][3] = 0.0;
		m[2][0] = 0.0f;
		m[2][1] = 0.0f;
		m[2][2] = (-p.zNear - p.zFar) / zRange;
		m[2][3] = 2.0f * p.zFar * p.zNear / zRange;
		m[3][0] = 0.0f;
		m[3][1] = 0.0f;
		m[3][2] = 1.0f;
		m[3][3] = 0.0;
	}

	void Matrix4::InitOrthoProjTransform(const OrthoProjInfo& p) {
		float l = p.l;
		float r = p.r;
		float b = p.b;
		float t = p.t;
		float n = p.n;
		float f = p.f;

		m[0][0] = 2.0f / (r - l);
		m[0][1] = 0.0f;
		m[0][2] = 0.0f;
		m[0][3] = -(r + l) / (r - l);
		m[1][0] = 0.0f;
		m[1][1] = 2.0f / (t - b);
		m[1][2] = 0.0f;
		m[1][3] = -(t + b) / (t - b);
		m[2][0] = 0.0f;
		m[2][1] = 0.0f;
		m[2][2] = 2.0f / (f - n);
		m[2][3] = -(f + n) / (f - n);
		m[3][0] = 0.0f;
		m[3][1] = 0.0f;
		m[3][2] = 0.0f;
		m[3][3] = 1.0;
	}

	float Matrix4::Determinant() const {
		return m[0][0] * m[1][1] * m[2][2] * m[3][3] - m[0][0] * m[1][1] * m[2][3] * m[3][2] + m[0][0] * m[1][2] * m[2][3] * m[3][1] - m[0][0] * m[1][2] * m[2][1] * m[3][3]
			+ m[0][0] * m[1][3] * m[2][1] * m[3][2] - m[0][0] * m[1][3] * m[2][2] * m[3][1] - m[0][1] * m[1][2] * m[2][3] * m[3][0] + m[0][1] * m[1][2] * m[2][0] * m[3][3]
			- m[0][1] * m[1][3] * m[2][0] * m[3][2] + m[0][1] * m[1][3] * m[2][2] * m[3][0] - m[0][1] * m[1][0] * m[2][2] * m[3][3] + m[0][1] * m[1][0] * m[2][3] * m[3][2]
			+ m[0][2] * m[1][3] * m[2][0] * m[3][1] - m[0][2] * m[1][3] * m[2][1] * m[3][0] + m[0][2] * m[1][0] * m[2][1] * m[3][3] - m[0][2] * m[1][0] * m[2][3] * m[3][1]
			+ m[0][2] * m[1][1] * m[2][3] * m[3][0] - m[0][2] * m[1][1] * m[2][0] * m[3][3] - m[0][3] * m[1][0] * m[2][1] * m[3][2] + m[0][3] * m[1][0] * m[2][2] * m[3][1]
			- m[0][3] * m[1][1] * m[2][2] * m[3][0] + m[0][3] * m[1][1] * m[2][0] * m[3][2] - m[0][3] * m[1][2] * m[2][0] * m[3][1] + m[0][3] * m[1][2] * m[2][1] * m[3][0];
	}

	Matrix4& Matrix4::Inverse() {
		// Compute the reciprocal determinant
		float det = Determinant();
		if (det == 0.0f) {
			// Matrix not invertible. Setting all elements to nan is not really
			// correct in a mathematical sense but it is easy to debug for the
			// programmer.
			/*const float nan = std::numeric_limits<float>::quiet_NaN();
			*this = Matrix4(
			nan,nan,nan,nan,
			nan,nan,nan,nan,
			nan,nan,nan,nan,
			nan,nan,nan,nan);*/
			assert(0);
			return *this;
		}

		float invdet = 1.0f / det;

		Zen::Matrix4 res;
		res.m[0][0] = invdet * (m[1][1] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) + m[1][2] * (m[2][3] * m[3][1] - m[2][1] * m[3][3]) + m[1][3] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]));
		res.m[0][1] = -invdet * (m[0][1] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) + m[0][2] * (m[2][3] * m[3][1] - m[2][1] * m[3][3]) + m[0][3] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]));
		res.m[0][2] = invdet * (m[0][1] * (m[1][2] * m[3][3] - m[1][3] * m[3][2]) + m[0][2] * (m[1][3] * m[3][1] - m[1][1] * m[3][3]) + m[0][3] * (m[1][1] * m[3][2] - m[1][2] * m[3][1]));
		res.m[0][3] = -invdet * (m[0][1] * (m[1][2] * m[2][3] - m[1][3] * m[2][2]) + m[0][2] * (m[1][3] * m[2][1] - m[1][1] * m[2][3]) + m[0][3] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]));
		res.m[1][0] = -invdet * (m[1][0] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) + m[1][2] * (m[2][3] * m[3][0] - m[2][0] * m[3][3]) + m[1][3] * (m[2][0] * m[3][2] - m[2][2] * m[3][0]));
		res.m[1][1] = invdet * (m[0][0] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) + m[0][2] * (m[2][3] * m[3][0] - m[2][0] * m[3][3]) + m[0][3] * (m[2][0] * m[3][2] - m[2][2] * m[3][0]));
		res.m[1][2] = -invdet * (m[0][0] * (m[1][2] * m[3][3] - m[1][3] * m[3][2]) + m[0][2] * (m[1][3] * m[3][0] - m[1][0] * m[3][3]) + m[0][3] * (m[1][0] * m[3][2] - m[1][2] * m[3][0]));
		res.m[1][3] = invdet * (m[0][0] * (m[1][2] * m[2][3] - m[1][3] * m[2][2]) + m[0][2] * (m[1][3] * m[2][0] - m[1][0] * m[2][3]) + m[0][3] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]));
		res.m[2][0] = invdet * (m[1][0] * (m[2][1] * m[3][3] - m[2][3] * m[3][1]) + m[1][1] * (m[2][3] * m[3][0] - m[2][0] * m[3][3]) + m[1][3] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]));
		res.m[2][1] = -invdet * (m[0][0] * (m[2][1] * m[3][3] - m[2][3] * m[3][1]) + m[0][1] * (m[2][3] * m[3][0] - m[2][0] * m[3][3]) + m[0][3] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]));
		res.m[2][2] = invdet * (m[0][0] * (m[1][1] * m[3][3] - m[1][3] * m[3][1]) + m[0][1] * (m[1][3] * m[3][0] - m[1][0] * m[3][3]) + m[0][3] * (m[1][0] * m[3][1] - m[1][1] * m[3][0]));
		res.m[2][3] = -invdet * (m[0][0] * (m[1][1] * m[2][3] - m[1][3] * m[2][1]) + m[0][1] * (m[1][3] * m[2][0] - m[1][0] * m[2][3]) + m[0][3] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]));
		res.m[3][0] = -invdet * (m[1][0] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]) + m[1][1] * (m[2][2] * m[3][0] - m[2][0] * m[3][2]) + m[1][2] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]));
		res.m[3][1] = invdet * (m[0][0] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]) + m[0][1] * (m[2][2] * m[3][0] - m[2][0] * m[3][2]) + m[0][2] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]));
		res.m[3][2] = -invdet * (m[0][0] * (m[1][1] * m[3][2] - m[1][2] * m[3][1]) + m[0][1] * (m[1][2] * m[3][0] - m[1][0] * m[3][2]) + m[0][2] * (m[1][0] * m[3][1] - m[1][1] * m[3][0]));
		res.m[3][3] = invdet * (m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) + m[0][1] * (m[1][2] * m[2][0] - m[1][0] * m[2][2]) + m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]));
		*this = res;

		return *this;
	}
}
