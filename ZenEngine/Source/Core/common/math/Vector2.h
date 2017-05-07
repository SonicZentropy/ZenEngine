// // /**
// //  * Vector2.h
// //  * Dylan Bailey
// //  * 20170507
// // */

#pragma once

namespace Zen
{
	template <typename T>
	struct CVector2
	{
		T x, y;
		CVector2();
		CVector2(T inX, T inY);
		template <typename U>
		explicit CVector2(const CVector2<U>& vector);

		~CVector2() {};

	};

	template <typename T>
	CVector2<T> operator -(const CVector2<T>& left);

	template <typename T>
	CVector2<T>& operator +=(CVector2<T>& left, const CVector2<T>& right);

	template <typename T>
	CVector2<T>& operator -=(CVector2<T>& left, const CVector2<T>& right);

	template <typename T>
	CVector2<T> operator +(const CVector2<T>& left, const CVector2<T>& right);

	template <typename T>
	CVector2<T> operator -(const CVector2<T>& left, const CVector2<T>& right);

	template <typename T>
	CVector2<T> operator *(const CVector2<T>& left, T right);

	template <typename T>
	CVector2<T> operator *(T left, const CVector2<T>& right);

	template <typename T>
	CVector2<T>& operator *=(CVector2<T>& left, T right);

	template <typename T>
	CVector2<T> operator /(const CVector2<T>& left, T right);

	template <typename T>
	CVector2<T>& operator /=(CVector2<T>& left, T right);

	template <typename T>
	bool operator ==(const CVector2<T>& left, const CVector2<T>& right);

	template <typename T>
	bool operator !=(const CVector2<T>& left, const CVector2<T>& right);

	///////////////////////////////////////////////////////////////////
	// INLINE TEMPLATE
	//////////////////////////////////////////////////////////////////



	template <typename T>
	inline CVector2<T>::CVector2() :
		x(0),
		y(0)

	{

	}


	////////////////////////////////////////////////////////////
	template <typename T>
	inline CVector2<T>::CVector2(T X, T Y) :
		x(X),
		y(Y)
	{

	}


	////////////////////////////////////////////////////////////
	template <typename T>
	template <typename U>
	inline CVector2<T>::CVector2(const CVector2<U>& vector) :
		x(static_cast<T>(vector.x)),
		y(static_cast<T>(vector.y))

	{
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	inline CVector2<T> operator -(const CVector2<T>& left)
	{
		return CVector2<T>(-left.x, -left.y);
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	inline CVector2<T>& operator +=(CVector2<T>& left, const CVector2<T>& right)
	{
		left.x += right.x;
		left.y += right.y;


		return left;
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	inline CVector2<T>& operator -=(CVector2<T>& left, const CVector2<T>& right)
	{
		left.x -= right.x;
		left.y -= right.y;


		return left;
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	inline CVector2<T> operator +(const CVector2<T>& left, const CVector2<T>& right)
	{
		return CVector2<T>(left.x + right.x, left.y + right.y);
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	inline CVector2<T> operator -(const CVector2<T>& left, const CVector2<T>& right)
	{
		return CVector2<T>(left.x - right.x, left.y - right.y);
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	inline CVector2<T> operator *(const CVector2<T>& left, T right)
	{
		return CVector2<T>(left.x * right, left.y * right);
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	inline CVector2<T> operator *(T left, const CVector2<T>& right)
	{
		return CVector2<T>(right.x * left, right.y * left);
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	inline CVector2<T>& operator *=(CVector2<T>& left, T right)
	{
		left.x *= right;
		left.y *= right;


		return left;
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	inline CVector2<T> operator /(const CVector2<T>& left, T right)
	{
		return CVector2<T>(left.x / right, left.y / right);
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	inline CVector2<T>& operator /=(CVector2<T>& left, T right)
	{
		left.x /= right;
		left.y /= right;


		return left;
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	inline bool operator ==(const CVector2<T>& left, const CVector2<T>& right)
	{
		return (left.x == right.x) && (left.y == right.y);
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	inline bool operator !=(const CVector2<T>& left, const CVector2<T>& right)
	{
		return (left.x != right.x) || (left.y != right.y);
	}

	using Vector2 = CVector2<float>;
}
