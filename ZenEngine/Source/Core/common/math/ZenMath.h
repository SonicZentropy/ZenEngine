// // /**
// //  * ZenMath.h
// //  * Dylan Bailey
// //  * 20170507
// // */

#pragma once

namespace Zen
{
#define ToRadian(x) (float)(((x) * M_PI / 180.0f))
#define ToDegree(x) (float)(((x) * 180.0f / M_PI))

	struct PersProjInfo
	{
		float FOV;
		float Width;
		float Height;
		float zNear;
		float zFar;
	};


	struct OrthoProjInfo
	{
		float r;        // right
		float l;        // left
		float b;        // bottom
		float t;        // top
		float n;        // z near
		float f;        // z far
	};

	class ZenMath
	{
	public:
		//static Vector3 Cross()
	};

	template <typename T>
	struct CVector3
	{
		T x, y, z;
		CVector3();
		CVector3(T inX, T inY, T inZ);
		template <typename U>
		explicit CVector3(const CVector3<U>& vector);

		const static CVector3<T> Zero;
		const static CVector3<T> One;
		const static CVector3<T> Up;
		const static CVector3<T> Right;
		const static CVector3<T> Forward;

		CVector3<T> Cross(const CVector3<T>& other) const {
			const T _x = y * other.z - z * other.y;
			const T _y = z * other.x - x * other.z;
			const T _z = x * other.y - y * other.x;

			return CVector3<T>(_x, _y, _z);
		}

		CVector3<T> Normalize()
		{
			const T Length = sqrtf(x * x + y * y + z * z);

			x /= Length;
			y /= Length;
			z /= Length;

			return *this;
		}

		CVector3<T> normalized()
		{
			const T Length = sqrtf(x * x + y * y + z * z);
			CVector3<T> newVec;
			newVec.x /= Length;
			newVec.y /= Length;
			newVec.z /= Length;

			return newVec;
		}

		CVector3<T> Rotate(float Angle, const CVector3<T>& Axe);

		~CVector3() {};

	};

	template <typename T>
	struct CQuaternion
	{
		T x, y, z, w;
		CQuaternion() {};
		CQuaternion(T inX, T inY, T inZ, T inW)
			: x(inX), y(inY), z(inZ), w(inW)
		{};

		const static CQuaternion<T> Identity;

		CQuaternion<T> Normalize();

		CQuaternion<T> Conjugate();

		//CQuaternion<T> operator*(const CQuaternion<T>& l, const CQuaternion<T>& r);

		//CQuaternion<T> operator*(const CQuaternion<T>& q, const Vector3& v);



		CVector3<T> ToDegrees();
	};

	template <typename T>
	CVector3<T> operator -(const CVector3<T>& left);

	template <typename T>
	CVector3<T>& operator +=(CVector3<T>& left, const CVector3<T>& right);

	template <typename T>
	CVector3<T>& operator -=(CVector3<T>& left, const CVector3<T>& right);

	template <typename T>
	CVector3<T> operator +(const CVector3<T>& left, const CVector3<T>& right);

	template <typename T>
	CVector3<T> operator -(const CVector3<T>& left, const CVector3<T>& right);

	template <typename T>
	CVector3<T> operator *(const CVector3<T>& left, T right);

	template <typename T>
	CVector3<T> operator *(T left, const CVector3<T>& right);

	template <typename T>
	CVector3<T>& operator *=(CVector3<T>& left, T right);

	template <typename T>
	CVector3<T> operator /(const CVector3<T>& left, T right);

	template <typename T>
	CVector3<T>& operator /=(CVector3<T>& left, T right);

	template <typename T>
	bool operator ==(const CVector3<T>& left, const CVector3<T>& right);

	template <typename T>
	bool operator !=(const CVector3<T>& left, const CVector3<T>& right);

	///////////////////////////////////////////////////////////////////
	// INLINE TEMPLATE
	//////////////////////////////////////////////////////////////////

	template <typename T>
	CVector3<T>::CVector3() :
		x(0),
		y(0),
		z(0)
	{

	}


	////////////////////////////////////////////////////////////
	template <typename T>
	CVector3<T>::CVector3(T X, T Y, T Z) :
		x(X),
		y(Y),
		z(Z)
	{

	}


	////////////////////////////////////////////////////////////
	template <typename T>
	template <typename U>
	CVector3<T>::CVector3(const CVector3<U>& vector) :
		x(static_cast<T>(vector.x)),
		y(static_cast<T>(vector.y)),
		z(static_cast<T>(vector.z))
	{
	}


	template <typename T>
	CVector3<T> CVector3<T>::Rotate(float Angle, const CVector3<T>& Axe) {
		const float SinHalfAngle = sinf(ToRadian(Angle / 2));
		const float CosHalfAngle = cosf(ToRadian(Angle / 2));

		const float Rx = Axe.x * SinHalfAngle;
		const float Ry = Axe.y * SinHalfAngle;
		const float Rz = Axe.z * SinHalfAngle;
		const float Rw = CosHalfAngle;
		CQuaternion<T> RotationQ(Rx, Ry, Rz, Rw);

		CQuaternion<T> ConjugateQ = RotationQ.Conjugate();
		//  ConjugateQ.Normalize();
		CQuaternion<T> W = RotationQ * (*this) * ConjugateQ;

		x = W.x;
		y = W.y;
		z = W.z;

		return *this;
	}////////////////////////////////////////////////////////////
	template <typename T>
	CVector3<T> operator -(const CVector3<T>& left)
	{
		return CVector3<T>(-left.x, -left.y, -left.z);
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	CVector3<T>& operator +=(CVector3<T>& left, const CVector3<T>& right)
	{
		left.x += right.x;
		left.y += right.y;
		left.z += right.z;

		return left;
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	CVector3<T>& operator -=(CVector3<T>& left, const CVector3<T>& right)
	{
		left.x -= right.x;
		left.y -= right.y;
		left.z -= right.z;

		return left;
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	CVector3<T> operator +(const CVector3<T>& left, const CVector3<T>& right)
	{
		return CVector3<T>(left.x + right.x, left.y + right.y, left.z + right.z);
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	CVector3<T> operator -(const CVector3<T>& left, const CVector3<T>& right)
	{
		return CVector3<T>(left.x - right.x, left.y - right.y, left.z - right.z);
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	CVector3<T> operator *(const CVector3<T>& left, T right)
	{
		return CVector3<T>(left.x * right, left.y * right, left.z * right);
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	CVector3<T> operator *(T left, const CVector3<T>& right)
	{
		return CVector3<T>(right.x * left, right.y * left, right.z * left);
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	CVector3<T>& operator *=(CVector3<T>& left, T right)
	{
		left.x *= right;
		left.y *= right;
		left.z *= right;

		return left;
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	CVector3<T> operator /(const CVector3<T>& left, T right)
	{
		return CVector3<T>(left.x / right, left.y / right, left.z / right);
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	CVector3<T>& operator /=(CVector3<T>& left, T right)
	{
		left.x /= right;
		left.y /= right;
		left.z /= right;

		return left;
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	bool operator ==(const CVector3<T>& left, const CVector3<T>& right)
	{
		return (left.x == right.x) && (left.y == right.y) && (left.z == right.z);
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	bool operator !=(const CVector3<T>& left, const CVector3<T>& right)
	{
		return (left.x != right.x) || (left.y != right.y) || (left.z != right.z);
	}

	using Vector3 = CVector3<PrecisionType>;

	//const static Vector3 Zero = Vector3(0,0, 0);
	const CVector3<PrecisionType> CVector3<PrecisionType>::Zero = Vector3(0, 0, 0);
	const CVector3<PrecisionType> CVector3<PrecisionType>::One = Vector3(1, 1, 1);
	const CVector3<PrecisionType> CVector3<PrecisionType>::Up = Vector3(0, 1, 0);
	const CVector3<PrecisionType> CVector3<PrecisionType>::Right = Vector3(1, 0, 0);
	const CVector3<PrecisionType> CVector3<PrecisionType>::Forward = Vector3(0, 0, 1);

	template <typename T>
	CVector3<T> CQuaternion<T>::ToDegrees()
	{
		float f[3];

		f[0] = atan2(x * z + y * w, x * w - y * z);
		f[1] = acos(-x * x - y * y - z * z - w * w);
		f[2] = atan2(x * z - y * w, x * w + y * z);

		f[0] = ToDegree(f[0]);
		f[1] = ToDegree(f[1]);
		f[2] = ToDegree(f[2]);

		return CVector3<T>(f[0], f[1], f[2]);
	}

	template <typename T>
	CQuaternion<T> operator*(const CQuaternion<T>& l, const CQuaternion<T>& r)
	{
		const float w = (l.w * r.w) - (l.x * r.x) - (l.y * r.y) - (l.z * r.z);
		const float x = (l.x * r.w) + (l.w * r.x) + (l.y * r.z) - (l.z * r.y);
		const float y = (l.y * r.w) + (l.w * r.y) + (l.z * r.x) - (l.x * r.z);
		const float z = (l.z * r.w) + (l.w * r.z) + (l.x * r.y) - (l.y * r.x);

		CQuaternion<T> ret(x, y, z, w);

		return ret;
	}

	template <typename T>
	CQuaternion<T> operator*(const CQuaternion<T>& q, const CVector3<T>& v)
	{
		const float w = -(q.x * v.x) - (q.y * v.y) - (q.z * v.z);
		const float x = (q.w * v.x) + (q.y * v.z) - (q.z * v.y);
		const float y = (q.w * v.y) + (q.z * v.x) - (q.x * v.z);
		const float z = (q.w * v.z) + (q.x * v.y) - (q.y * v.x);

		CQuaternion<T> ret(x, y, z, w);

		return ret;
	}


	template <typename T>
	CQuaternion<T> CQuaternion<T>::Conjugate()
	{
		return CQuaternion<T>(-x, -y, -z, w);
	}

	template <typename T>
	CQuaternion<T> CQuaternion<T>::Normalize()
	{
		T Length = sqrt(x * x + y * y + z * z + w * w);

		x /= Length;
		y /= Length;
		z /= Length;
		w /= Length;
		return *this;
	}

	using Quaternion = CQuaternion<PrecisionType>;
	const CQuaternion<PrecisionType> CQuaternion<PrecisionType>::Identity = Quaternion(0, 0, 0, 1);
}
