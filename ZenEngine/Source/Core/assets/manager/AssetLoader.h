#pragma once

namespace Zen {
	class AssetLoader
	{
	public:
		AssetLoader();
		~AssetLoader();
		static GLuint LoadBMP_Custom(string imagepath);
		bool LoadFBX(string path);
	};

}
