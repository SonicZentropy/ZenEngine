// // /**
// //  * IRenderable.h
// //  * Dylan Bailey
// //  * 20170507
// // */

#pragma once

namespace Zen
{
	class IRenderable
	{
	public:
		virtual ~IRenderable() = default;
		virtual void Render() = 0;
	};
}
