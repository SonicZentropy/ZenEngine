﻿// // /**
// //  * Matrix4.hpp
// //  * Dylan Bailey
// //  * 20170507
// // */

#pragma once
#include <assimp/matrix4x4.h>
#include <assimp/matrix3x3.h>

namespace Zen
{
	struct PersProjInfo;
	struct OrthoProjInfo;

	class Matrix4
	{
	public:
		float m[4][4];

		Matrix4()
		{
		}

		// constructor from Assimp matrix
		Matrix4(const aiMatrix4x4& AssimpMatrix)
		{
			m[0][0] = AssimpMatrix.a1; m[0][1] = AssimpMatrix.a2; m[0][2] = AssimpMatrix.a3; m[0][3] = AssimpMatrix.a4;
			m[1][0] = AssimpMatrix.b1; m[1][1] = AssimpMatrix.b2; m[1][2] = AssimpMatrix.b3; m[1][3] = AssimpMatrix.b4;
			m[2][0] = AssimpMatrix.c1; m[2][1] = AssimpMatrix.c2; m[2][2] = AssimpMatrix.c3; m[2][3] = AssimpMatrix.c4;
			m[3][0] = AssimpMatrix.d1; m[3][1] = AssimpMatrix.d2; m[3][2] = AssimpMatrix.d3; m[3][3] = AssimpMatrix.d4;
		}

		Matrix4(const aiMatrix3x3& AssimpMatrix)
		{
			m[0][0] = AssimpMatrix.a1; m[0][1] = AssimpMatrix.a2; m[0][2] = AssimpMatrix.a3; m[0][3] = 0.0f;
			m[1][0] = AssimpMatrix.b1; m[1][1] = AssimpMatrix.b2; m[1][2] = AssimpMatrix.b3; m[1][3] = 0.0f;
			m[2][0] = AssimpMatrix.c1; m[2][1] = AssimpMatrix.c2; m[2][2] = AssimpMatrix.c3; m[2][3] = 0.0f;
			m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
		}

		Matrix4(float a00, float a01, float a02, float a03,
			float a10, float a11, float a12, float a13,
			float a20, float a21, float a22, float a23,
			float a30, float a31, float a32, float a33)
		{
			m[0][0] = a00; m[0][1] = a01; m[0][2] = a02; m[0][3] = a03;
			m[1][0] = a10; m[1][1] = a11; m[1][2] = a12; m[1][3] = a13;
			m[2][0] = a20; m[2][1] = a21; m[2][2] = a22; m[2][3] = a23;
			m[3][0] = a30; m[3][1] = a31; m[3][2] = a32; m[3][3] = a33;
		}

		void SetZero()
		{
			ZeroMemory(m, sizeof(Matrix4));
		}

		Matrix4 Transpose() const
		{
			Matrix4 n;

			for (unsigned int i = 0; i < 4; i++) {
				for (unsigned int j = 0; j < 4; j++) {
					n.m[i][j] = m[j][i];
				}
			}

			return n;
		}


		inline void InitIdentity()
		{
			m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
			m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
			m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
			m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
		}

		inline Matrix4 operator*(const Matrix4& Right) const
		{
			Matrix4 Ret;

			for (unsigned int i = 0; i < 4; i++) {
				for (unsigned int j = 0; j < 4; j++) {
					Ret.m[i][j] = m[i][0] * Right.m[0][j] +
						m[i][1] * Right.m[1][j] +
						m[i][2] * Right.m[2][j] +
						m[i][3] * Right.m[3][j];
				}
			}

			return Ret;
		}

		Vector4 operator*(const Vector4& v) const
		{
			Vector4 r;

			r.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w;
			r.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w;
			r.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w;
			r.w = m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w;

			return r;
		}

		operator const float*() const
		{
			return &(m[0][0]);
		}

		void Print() const
		{
			for (int i = 0; i < 4; i++) {
				printf("%f %f %f %f\n", m[i][0], m[i][1], m[i][2], m[i][3]);
			}
		}

		float Determinant() const;

		Matrix4& Inverse();

		void InitScaleTransform(float ScaleX, float ScaleY, float ScaleZ);
		void InitRotateTransform(float RotateX, float RotateY, float RotateZ);
		void InitRotateTransform(const Quaternion& quat);
		void InitTranslationTransform(float x, float y, float z);
		void InitCameraTransform(const Vector3& Target, const Vector3& Up);
		void InitPersProjTransform(const PersProjInfo& p);
		void InitOrthoProjTransform(const OrthoProjInfo& p);
	};
}
