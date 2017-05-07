// // /**
// //  * ObjModel.h
// //  * Dylan Bailey
// //  * 20170506
// // */

#pragma once

namespace Zen
{
	class ObjModel
	{
	public:
		vector<vec3> vertices;
		vector<vec2> UVs;
		vector<vec3> normals;
		vector<unsigned short> indices;

		ObjModel(const string& pathToLoad);
		bool LoadModel(const string& pathToLoad);
	};
}
