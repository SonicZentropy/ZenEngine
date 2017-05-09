// // /**
// //  * Pipeline3D.h
// //  * Dylan Bailey
// //  * 20170507
// // */

#pragma once

#include "Source/Core/common/math/Matrix4.hpp"
#include "Source/Core/camera/Camera3D.h"

namespace Zen
{
	struct Orientation3D
	{
		Vector3 scale;
		Vector3 position;
		Vector3 rotation;

		Orientation3D() {
			scale = Vector3::One;
			rotation = Vector3::Zero;
			position = Vector3::Zero;
		}
	};


	class Pipeline3D
	{
	public:
		Pipeline3D()
		{
			scale = Vector3(1.0f, 1.0f, 1.0f);
			worldPos = Vector3(0.0f, 0.0f, 0.0f);
			rotateInfo = Vector3(0.0f, 0.0f, 0.0f);
		}

		void Scale(float s)
		{
			Scale(s, s, s);
		}


		void Scale(const Vector3& scale)
		{
			Scale(scale.x, scale.y, scale.z);
		}

		void Scale(float ScaleX, float ScaleY, float ScaleZ)
		{
			scale.x = ScaleX;
			scale.y = ScaleY;
			scale.z = ScaleZ;
		}

		void WorldPos(float x, float y, float z)
		{
			worldPos.x = x;
			worldPos.y = y;
			worldPos.z = z;
		}

		void WorldPos(const Vector3& Pos)
		{
			worldPos = Pos;
		}

		void Rotate(float RotateX, float RotateY, float RotateZ)
		{
			rotateInfo.x = RotateX;
			rotateInfo.y = RotateY;
			rotateInfo.z = RotateZ;
		}

		void Rotate(const Vector3& r)
		{
			Rotate(r.x, r.y, r.z);
		}

		void SetPerspectiveProj(const PersProjInfo& p)
		{
			persProjInfo = p;
		}

		void SetOrthographicProj(const OrthoProjInfo& p)
		{
			orthoProjInfo = p;
		}

		void SetCamera(const Vector3& Pos, const Vector3& Target, const Vector3& Up)
		{
			camera.Pos = Pos;
			camera.Target = Target;
			camera.Up = Up;
		}

		void SetCamera(const Camera3D& camera)
		{
			SetCamera(camera.Position(), camera.Target(), camera.Up());
		}

		void Orient(const Orientation3D& o)
		{
			scale = o.scale;
			worldPos = o.position;
			rotateInfo = o.rotation;
		}

		const Matrix4& GetWPTrans();
		const Matrix4& GetWVTrans();
		const Matrix4& GetVPTrans();
		const Matrix4& GetWVPTrans();
		const Matrix4& GetWVOrthoPTrans();
		const Matrix4& GetWorldTrans();
		const Matrix4& GetViewTrans();
		const Matrix4& GetProjTrans();

	private:
		Vector3 scale;
		Vector3 worldPos;
		Vector3 rotateInfo;

		PersProjInfo persProjInfo;
		OrthoProjInfo orthoProjInfo;

		struct {
			Vector3 Pos;
			Vector3 Target;
			Vector3 Up;
		} camera;

		Matrix4 WVPtransformation;
		Matrix4 VPtransformation;
		Matrix4 WPtransformation;
		Matrix4 WVtransformation;
		Matrix4 Wtransformation;
		Matrix4 Vtransformation;
		Matrix4 ProjTransformation;
	};
}
