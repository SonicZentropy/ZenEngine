#pragma once
#include "Source/Core/assets/models/ObjModel.h"

namespace Zen {
	class AssetLoader
	{
	public:
		AssetLoader();
		~AssetLoader();
		static GLuint LoadBMP_Custom(string imagepath);
		static ObjModel LoadOBJ(string path);
		bool LoadFBX(string path);
	};

}
