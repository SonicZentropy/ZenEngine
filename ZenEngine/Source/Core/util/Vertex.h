// // /**
// //  * Vertex.h
// //  * Dylan Bailey
// //  * 20170507
// // */

#pragma once
//#include "Source/Core/common/math/Vector2.h"

namespace Zen
{
	struct Vertex
	{
		Vector3 position;
		Vector2 texture;
		Vector3 normal;

		Vertex(const Vector3& inPosition = Vector3(0, 0, 0)
			, const Vector2& inTexture = Vector2(0, 0)
			, const Vector3& inNormal = Vector3(0, 0, 0))
			:position(inPosition), texture(inTexture), normal(inNormal)
		{}
	};
}
