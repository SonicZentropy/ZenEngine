#include "stdafx.h"
#include "Camera3D.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include "Source/Base/Game.h"

namespace Zen
{
	const static float STEP_SCALE = 1.0f;
	const static float EDGE_STEP = 0.5f;
	const static int MARGIN = 10;

	Camera3D::Camera3D(int WindowWidth, int WindowHeight)
	{
		windowWidth = WindowWidth;
		windowHeight = WindowHeight;
		position = Vector3(0.0f, 0.0f, 0.0f);
		target = Vector3(0.0f, 0.0f, 1.0f);
		target.Normalize();
		up = Vector3(0.0f, 1.0f, 0.0f);

		Init();
	}


	Camera3D::Camera3D(int WindowWidth, int WindowHeight, const Vector3& Pos, const Vector3& Target, const Vector3& Up)
	{
		windowWidth = WindowWidth;
		windowHeight = WindowHeight;
		position = Pos;

		target = Target;
		target.Normalize();

		up = Up;
		up.Normalize();

		Init();
	}


	void Camera3D::Init()
	{
		Vector3 HTarget(target.x, 0.0, target.z);
		HTarget.Normalize();

		if (HTarget.z >= 0.0f)
		{
			if (HTarget.x >= 0.0f)
			{
				angleH = 360.0f - ToDegree(asin(HTarget.z));
			}
			else
			{
				angleH = 180.0f + ToDegree(asin(HTarget.z));
			}
		}
		else
		{
			if (HTarget.x >= 0.0f)
			{
				angleH = ToDegree(asin(-HTarget.z));
			}
			else
			{
				angleH = 180.0f - ToDegree(asin(-HTarget.z));
			}
		}

		angleV = -ToDegree(asin(target.y));

		onUpperEdge = false;
		onLowerEdge = false;
		onLeftEdge = false;
		onRightEdge = false;
		mousePos.x = windowWidth / 2;
		mousePos.y = windowHeight / 2;
	}

	void Camera3D::Update()
	{
		OnInput();
		const Vector3 Vaxis(0.0f, 1.0f, 0.0f);

		// Rotate the view vector by the horizontal angle around the vertical axis
		Vector3 View(1.0f, 0.0f, 0.0f);
		View.Rotate(angleH, Vaxis);
		View.Normalize();

		// Rotate the view vector by the vertical angle around the horizontal axis
		Vector3 Haxis = Vaxis.Cross(View);
		Haxis.Normalize();
		View.Rotate(angleV, Haxis);

		target = View;
		target.Normalize();

		up = target.Cross(Haxis);
		up.Normalize();
	}
	
	bool Camera3D::OnInput() {
		bool Ret = false;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			position += (target * STEP_SCALE);
			Ret = true;
		}

		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			position -= (target * STEP_SCALE);
			Ret = true;
		}
		

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			Vector3 Left = target.Cross(up);
			Left.Normalize();
			Left *= STEP_SCALE;
			position += Left;
			Ret = true;
		}
		

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			Vector3 Right = up.Cross(target);
			Right.Normalize();
			Right *= STEP_SCALE;
			position += Right;
			Ret = true;
		}
		

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp))
			position.y += STEP_SCALE;
			

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown))
			position.y -= STEP_SCALE;
		
		/////////////////////////////////MOUSE
		//void Camera3D::OnMouse(int x, int y)
		auto currPos = sf::Mouse::getPosition(*(Game::currentWindow));
			const int DeltaX = currPos.x - mousePos.x;
			const int DeltaY = currPos.y - mousePos.y;

			mousePos.x = currPos.x;
			mousePos.y = currPos.y;

			angleH += (float)DeltaX / 20.0f;
			angleV += (float)DeltaY / 20.0f;

			if (DeltaX == 0) {
				if (currPos.x <= MARGIN) {
					//    angleH -= 1.0f;
					onLeftEdge = true;
				}
				else if (currPos.x >= (windowWidth - MARGIN)) {
					//    angleH += 1.0f;
					onRightEdge = true;
				}
			}
			else {
				onLeftEdge = false;
				onRightEdge = false;
			}

			if (DeltaY == 0) {
				if (currPos.y <= MARGIN) {
					onUpperEdge = true;
				}
				else if (currPos.y >= (windowHeight - MARGIN)) {
					onLowerEdge = true;
				}
			}
			else {
				onUpperEdge = false;
				onLowerEdge = false;
			}

		return Ret;
	}

	void Camera3D::Render()
	{
		bool ShouldUpdate = false;

		if (onLeftEdge) {
			angleH -= EDGE_STEP;
			ShouldUpdate = true;
		}
		else if (onRightEdge) {
			angleH += EDGE_STEP;
			ShouldUpdate = true;
		}

		if (onUpperEdge) {
			if (angleV > -90.0f) {
				angleV -= EDGE_STEP;
				ShouldUpdate = true;
			}
		}
		else if (onLowerEdge) {
			if (angleV < 90.0f) {
				angleV += EDGE_STEP;
				ShouldUpdate = true;
			}
		}

		if (ShouldUpdate) {
			Update();
		}
	}

	
}
