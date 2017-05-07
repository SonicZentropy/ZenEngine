#pragma once

namespace Zen::Assets {
	class AssetLoader
	{
	public:
		AssetLoader();
		~AssetLoader();
		static GLuint LoadBMP_Custom(string imagepath);
	};

}