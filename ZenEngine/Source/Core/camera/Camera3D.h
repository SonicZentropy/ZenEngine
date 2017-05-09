// // /**
// //  * Camera3D.h
// //  * Dylan Bailey
// //  * 20170507
// // */

#pragma once
#include "Source/Core/assets/models/IRenderable.h"

namespace Zen
{
	enum ECameraMovement
	{
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};

	class Camera3D : IRenderable
	{
	public:
		
		Camera3D(int Width, int Height);
		Camera3D(int Width, int Height, const Vector3& Pos, const Vector3& Target, const Vector3& Up);

		bool OnInput();

		void Render();

		const Vector3& Position() const {
			return position;
		}

		const Vector3& Target() const {
			return target;
		}

		const Vector3& Up() const {
			return up;
		}

	private:
		void Init();
		void Update();

		Vector3 position;
		Vector3 target;
		Vector3 up;

		int windowWidth, windowHeight;
		PrecisionType angleH, angleV;

		bool onUpperEdge, onLowerEdge, onLeftEdge, onRightEdge;

		Vector2i mousePos;
	};
}
