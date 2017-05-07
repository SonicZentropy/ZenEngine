// // /**
// //  * Vector3.h
// //  * Dylan Bailey
// //  * 20170507
// // */

#pragma once

namespace Zen
{
	template <typename T>
	struct CVector3
	{
		T x, y, z;
		CVector3();
		CVector3(T inX, T inY, T inZ);
		template <typename U>
		explicit CVector3(const CVector3<U>& vector);

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



		~CVector3() {};
		
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
	inline CVector3<T>::CVector3() :
		x(0),
		y(0),
		z(0)
	{

	}


	////////////////////////////////////////////////////////////
	template <typename T>
	inline CVector3<T>::CVector3(T X, T Y, T Z) :
		x(X),
		y(Y),
		z(Z)
	{

	}


	////////////////////////////////////////////////////////////
	template <typename T>
	template <typename U>
	inline CVector3<T>::CVector3(const CVector3<U>& vector) :
		x(static_cast<T>(vector.x)),
		y(static_cast<T>(vector.y)),
		z(static_cast<T>(vector.z))
	{
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	inline CVector3<T> operator -(const CVector3<T>& left)
	{
		return CVector3<T>(-left.x, -left.y, -left.z);
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	inline CVector3<T>& operator +=(CVector3<T>& left, const CVector3<T>& right)
	{
		left.x += right.x;
		left.y += right.y;
		left.z += right.z;

		return left;
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	inline CVector3<T>& operator -=(CVector3<T>& left, const CVector3<T>& right)
	{
		left.x -= right.x;
		left.y -= right.y;
		left.z -= right.z;

		return left;
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	inline CVector3<T> operator +(const CVector3<T>& left, const CVector3<T>& right)
	{
		return CVector3<T>(left.x + right.x, left.y + right.y, left.z + right.z);
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	inline CVector3<T> operator -(const CVector3<T>& left, const CVector3<T>& right)
	{
		return CVector3<T>(left.x - right.x, left.y - right.y, left.z - right.z);
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	inline CVector3<T> operator *(const CVector3<T>& left, T right)
	{
		return CVector3<T>(left.x * right, left.y * right, left.z * right);
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	inline CVector3<T> operator *(T left, const CVector3<T>& right)
	{
		return CVector3<T>(right.x * left, right.y * left, right.z * left);
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	inline CVector3<T>& operator *=(CVector3<T>& left, T right)
	{
		left.x *= right;
		left.y *= right;
		left.z *= right;

		return left;
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	inline CVector3<T> operator /(const CVector3<T>& left, T right)
	{
		return CVector3<T>(left.x / right, left.y / right, left.z / right);
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	inline CVector3<T>& operator /=(CVector3<T>& left, T right)
	{
		left.x /= right;
		left.y /= right;
		left.z /= right;

		return left;
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	inline bool operator ==(const CVector3<T>& left, const CVector3<T>& right)
	{
		return (left.x == right.x) && (left.y == right.y) && (left.z == right.z);
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	inline bool operator !=(const CVector3<T>& left, const CVector3<T>& right)
	{
		return (left.x != right.x) || (left.y != right.y) || (left.z != right.z);
	}

	using Vector3 = CVector3<float>;
}
