#pragma once

namespace Zen
{

#define ToRadian(x) (float)(((x) * M_PI / 180.0f))
#define ToDegree(x) (float)(((x) * 180.0f / M_PI))

	template <typename T>
	struct CQuaternion
	{
		T x, y, z, w;
		CQuaternion() {};
		CQuaternion(T inX, T inY, T inZ, T inW)
			: x(inX), y(inY), z(inZ), w(inW)
		{};
				
		const static CQuaternion<T> Identity;

		CQuaternion<T> Normalize() {
			T Length = sqrt(x * x + y * y + z * z + w * w);

			x /= Length;
			y /= Length;
			z /= Length;
			w /= Length;
			return *this;
		}

		CQuaternion<T> Conjugate() {
			return CQuaternion<T>(-x, -y, -z, w);			
		}

		CQuaternion<T> operator*(const CQuaternion<T>& l, const CQuaternion<T>& r)
		{
			const float w = (l.w * r.w) - (l.x * r.x) - (l.y * r.y) - (l.z * r.z);
			const float x = (l.x * r.w) + (l.w * r.x) + (l.y * r.z) - (l.z * r.y);
			const float y = (l.y * r.w) + (l.w * r.y) + (l.z * r.x) - (l.x * r.z);
			const float z = (l.z * r.w) + (l.w * r.z) + (l.x * r.y) - (l.y * r.x);

			CQuaternion<T> ret(x, y, z, w);

			return ret;
		}

		CQuaternion<T> operator*(const CQuaternion<T>& q, const Vector3& v)
		{
			const float w = -(q.x * v.x) - (q.y * v.y) - (q.z * v.z);
			const float x = (q.w * v.x) + (q.y * v.z) - (q.z * v.y);
			const float y = (q.w * v.y) + (q.z * v.x) - (q.x * v.z);
			const float z = (q.w * v.z) + (q.x * v.y) - (q.y * v.x);

			CQuaternion<T> ret(x, y, z, w);

			return ret;
		}


		Vector3 ToDegrees()
		{
			float f[3];

			f[0] = atan2(x * z + y * w, x * w - y * z);
			f[1] = acos(-x * x - y * y - z * z - w * w);
			f[2] = atan2(x * z - y * w, x * w + y * z);

			f[0] = ToDegree(f[0]);
			f[1] = ToDegree(f[1]);
			f[2] = ToDegree(f[2]);

			return Vector3(f[0], f[1], f[2]);
		}
	};

	using Quaternion = CQuaternion<PrecisionType>;
	const CQuaternion<PrecisionType> CQuaternion<PrecisionType>::Identity = Quaternion(0, 0, 0, 1);
}