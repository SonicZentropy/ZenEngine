// // /**
// //  * ShaderManager.h
// //  * Dylan Bailey
// //  * 20170429
// // */

#pragma once
#include <GL/glew.h>


namespace Zen
{
	class ShaderManager
	{
	public:
		static GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
	};
}
