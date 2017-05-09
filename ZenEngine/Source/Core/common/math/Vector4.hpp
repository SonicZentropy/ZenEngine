// // /**
// //  * Vector4.h
// //  * Dylan Bailey
// //  * 20170507
// // */

#pragma once
#include "Source/Core/common/math/Quaternion.hpp"

namespace Zen
{
	template <typename T>
	struct CVector4
	{
		T x, y, z, w;
		CVector4();
		CVector4(T inX, T inY, T inZ, T inW);
		template <typename U>
		explicit CVector4(const CVector4<U>& vector);

		const static CVector4<T> Zero;
		const static CVector4<T> One;
				

		CVector4<T> Normalize()
		{
			const T Length = sqrtf(x * x + y * y + z * z + w * w);

			x /= Length;
			y /= Length;
			z /= Length;
			w /= Length;

			return *this;
		}

		CVector4<T> normalized()
		{
			const T Length = sqrtf(x * x + y * y + z * z + w * w);
			CVector4<T> newVec;
			newVec.x /= Length;
			newVec.y /= Length;
			newVec.z /= Length;
			newVec.w /= Length;

			return newVec;
		}
		~CVector4() {};

	};

	template <typename T>
	CVector4<T> operator -(const CVector4<T>& left);

	template <typename T>
	CVector4<T>& operator +=(CVector4<T>& left, const CVector4<T>& right);

	template <typename T>
	CVector4<T>& operator -=(CVector4<T>& left, const CVector4<T>& right);

	template <typename T>
	CVector4<T> operator +(const CVector4<T>& left, const CVector4<T>& right);

	template <typename T>
	CVector4<T> operator -(const CVector4<T>& left, const CVector4<T>& right);

	template <typename T>
	CVector4<T> operator *(const CVector4<T>& left, T right);

	template <typename T>
	CVector4<T> operator *(T left, const CVector4<T>& right);

	template <typename T>
	CVector4<T>& operator *=(CVector4<T>& left, T right);

	template <typename T>
	CVector4<T> operator /(const CVector4<T>& left, T right);

	template <typename T>
	CVector4<T>& operator /=(CVector4<T>& left, T right);

	template <typename T>
	bool operator ==(const CVector4<T>& left, const CVector4<T>& right);

	template <typename T>
	bool operator !=(const CVector4<T>& left, const CVector4<T>& right);

	///////////////////////////////////////////////////////////////////
	// INLINE TEMPLATE
	//////////////////////////////////////////////////////////////////

	template <typename T>
	inline CVector4<T>::CVector4() :
		x(0),
		y(0),
		z(0),
		w(0)
	{

	}


	////////////////////////////////////////////////////////////
	template <typename T>
	inline CVector4<T>::CVector4(T X, T Y, T Z, T W) :
		x(X),
		y(Y),
		z(Z),
		w(W)
	{

	}


	////////////////////////////////////////////////////////////
	template <typename T>
	template <typename U>
	inline CVector4<T>::CVector4(const CVector4<U>& vector) :
		x(static_cast<T>(vector.x)),
		y(static_cast<T>(vector.y)),
		z(static_cast<T>(vector.z)),
		w(static_cast<T>(vector.w))
	{
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	inline CVector4<T> operator -(const CVector4<T>& left)
	{
		return CVector4<T>(-left.x, -left.y, -left.z, -left.w);
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	inline CVector4<T>& operator +=(CVector4<T>& left, const CVector4<T>& right)
	{
		left.x += right.x;
		left.y += right.y;
		left.z += right.z;
		left.w += right.w;

		return left;
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	inline CVector4<T>& operator -=(CVector4<T>& left, const CVector4<T>& right)
	{
		left.x -= right.x;
		left.y -= right.y;
		left.z -= right.z;
		left.w -= right.w;

		return left;
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	inline CVector4<T> operator +(const CVector4<T>& left, const CVector4<T>& right)
	{
		return CVector4<T>(left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w);
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	inline CVector4<T> operator -(const CVector4<T>& left, const CVector4<T>& right)
	{
		return CVector4<T>(left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w);
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	inline CVector4<T> operator *(const CVector4<T>& left, T right)
	{
		return CVector4<T>(left.x * right, left.y * right, left.z * right, left.w * right);
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	inline CVector4<T> operator *(T left, const CVector4<T>& right)
	{
		return CVector4<T>(right.x * left, right.y * left, right.z * left, right.w * left);
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	inline CVector4<T>& operator *=(CVector4<T>& left, T right)
	{
		left.x *= right;
		left.y *= right;
		left.z *= right;
		left.w *= right;

		return left;
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	inline CVector4<T> operator /(const CVector4<T>& left, T right)
	{
		return CVector4<T>(left.x / right, left.y / right, left.z / right, left.w / right);
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	inline CVector4<T>& operator /=(CVector4<T>& left, T right)
	{
		left.x /= right;
		left.y /= right;
		left.z /= right;
		left.w /= right;

		return left;
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	inline bool operator ==(const CVector4<T>& left, const CVector4<T>& right)
	{
		return (left.x == right.x) && (left.y == right.y) && (left.z == right.z) && (left.w == right.w);
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	inline bool operator !=(const CVector4<T>& left, const CVector4<T>& right)
	{
		return (left.x != right.x) || (left.y != right.y) || (left.z != right.z) || (left.w != right.w);
	}

	using Vector4 = CVector4<PrecisionType>;

	//const static Vector4 Zero = Vector4(0,0, 0);
	const CVector4<PrecisionType> CVector4<PrecisionType>::Zero = Vector4(0, 0, 0, 0);
	const CVector4<PrecisionType> CVector4<PrecisionType>::One = Vector4(1, 1, 1, 1);
}
