#include "stdafx.h"
#include "ObjModel.h"
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
//#include <boost/foreach.hpp>

namespace Zen
{
	ObjModel::ObjModel(const string& pathToLoad) {
		LoadModel(pathToLoad);
	}

	bool ObjModel::LoadModel(const string& pathToLoad) {
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(pathToLoad,
			aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);

		if (!scene) {
			LOG_DEBUG(importer.GetErrorString());
			return false;
		}
		int ji = scene->mNumMeshes;

		//const aiMesh* mesh = scene->mMeshes[0]; // In this simple example code we always use the 1rst mesh (in OBJ files there is often only one anyway)

												// Fill vertices positions
		//BOOST_FOREACH(aiMesh* mesh, scene->mMeshes)
		for (int zi = 0; zi < ji; ++zi)
		{
			aiMesh* mesh = scene->mMeshes[zi];
			//vertices.reserve(mesh->mNumVertices);
			for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
				aiVector3D pos = mesh->mVertices[i];
				vertices.push_back(vec3(pos.x, pos.y, pos.z));
			}

			// Fill vertices texture coordinates
			UVs.reserve(mesh->mNumVertices);
			for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
				aiVector3D UVW = mesh->mTextureCoords[0][i]; // Assume only 1 set of UV coords; AssImp supports 8 UV sets.
				UVs.push_back(vec2(UVW.x, UVW.y));
			}

			// Fill vertices normals
			normals.reserve(mesh->mNumVertices);
			for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
				aiVector3D n = mesh->mNormals[i];
				normals.push_back(vec3(n.x, n.y, n.z));
			}


			// Fill face indices
			indices.reserve(3 * mesh->mNumFaces);
			for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
				// Assume the model has only triangles.
				indices.push_back(mesh->mFaces[i].mIndices[0]);
				indices.push_back(mesh->mFaces[i].mIndices[1]);
				indices.push_back(mesh->mFaces[i].mIndices[2]);
			}
		}
		// The "scene" pointer will be deleted automatically by "importer"
		return true;
	}
}
