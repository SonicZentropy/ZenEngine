#include "stdafx.h"
#include "Pipeline3D.h"

namespace Zen
{
	

	const Matrix4& Pipeline3D::GetProjTrans()
	{
		ProjTransformation.InitPersProjTransform(persProjInfo);
		return ProjTransformation;
	}


	const Matrix4& Pipeline3D::GetVPTrans()
	{
		GetViewTrans();
		GetProjTrans();

		VPtransformation = ProjTransformation * Vtransformation;
		return VPtransformation;
	}

	const Matrix4& Pipeline3D::GetWorldTrans()
	{
		Matrix4 ScaleTrans, RotateTrans, TranslationTrans;

		ScaleTrans.InitScaleTransform(scale.x, scale.y, scale.z);
		RotateTrans.InitRotateTransform(rotateInfo.x, rotateInfo.y, rotateInfo.z);
		TranslationTrans.InitTranslationTransform(worldPos.x, worldPos.y, worldPos.z);

		Wtransformation = TranslationTrans * RotateTrans * ScaleTrans;
		return Wtransformation;
	}

	const Matrix4& Pipeline3D::GetViewTrans()
	{
		Matrix4 CameraTranslationTrans, CameraRotateTrans;

		CameraTranslationTrans.InitTranslationTransform(-camera.Pos.x, -camera.Pos.y, -camera.Pos.z);
		CameraRotateTrans.InitCameraTransform(camera.Target, camera.Up);

		Vtransformation = CameraRotateTrans * CameraTranslationTrans;

		return Vtransformation;
	}

	const Matrix4& Pipeline3D::GetWVPTrans()
	{
		GetWorldTrans();
		GetVPTrans();

		WVPtransformation = VPtransformation * Wtransformation;
		return WVPtransformation;
	}


	const Matrix4& Pipeline3D::GetWVOrthoPTrans()
	{
		GetWorldTrans();
		GetViewTrans();

		Matrix4 P;
		P.InitOrthoProjTransform(orthoProjInfo);

		WVPtransformation = P * Vtransformation * Wtransformation;
		return WVPtransformation;
	}


	const Matrix4& Pipeline3D::GetWVTrans()
	{
		GetWorldTrans();
		GetViewTrans();

		WVtransformation = Vtransformation * Wtransformation;
		return WVtransformation;
	}


	const Matrix4& Pipeline3D::GetWPTrans()
	{
		Matrix4 PersProjTrans;

		GetWorldTrans();
		PersProjTrans.InitPersProjTransform(persProjInfo);

		WPtransformation = PersProjTrans * Wtransformation;
		return WPtransformation;
	}
}
