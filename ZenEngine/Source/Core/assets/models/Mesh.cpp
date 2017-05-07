#include "stdafx.h"
#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <SFML/System/Vector3.hpp>
#include <boost/mpl/assert.hpp>

namespace Zen
{
	Mesh::Mesh() {}
	Mesh::~Mesh() {}

	bool Mesh::LoadMesh(const string& filename, unsigned processingFlags) {
		//Release previously loaded mesh if exists
		Clear();

		bool ret = false;
		Assimp::Importer importer;

		if (processingFlags == 0)
			processingFlags = aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices;
		//aiProcess_FlipUVsv - flip the texture coordinates along the Y axis. This was required in order to render the Quake model that was used for the demo correctly. 
		const aiScene* pScene = importer.ReadFile(filename.c_str(), processingFlags);

		if (pScene) {
			ret = InitFromScene(pScene, filename);
		}
		else {
			LOG_TRACE("Error parsing {} : {}", filename, importer.GetErrorString());
		}

		return ret;
	}

	bool Mesh::InitFromScene(const aiScene* pScene, const string& filename) {
		submeshes.resize(pScene->mNumMeshes);
		textures.resize(pScene->mNumMaterials);

		//init meshes one by one
		for (size_t i = 0; i < submeshes.size(); ++i) {
			const aiMesh* paiMesh = pScene->mMeshes[i];
			InitMesh(i, paiMesh);
		}

		return InitMaterials(pScene, filename);

	}

	void Mesh::InitMesh(unsigned int Index, const aiMesh* paiMesh) {
		submeshes[Index].materialIndex = paiMesh->mMaterialIndex;

		vector<Vertex> vertices;
		vector<unsigned int> indices;

		const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

		for (unsigned int i = 0; i < paiMesh->mNumVertices; ++i) {
			const aiVector3D* pPos = &(paiMesh->mVertices[i]);
			const aiVector3D* pNormal = &(paiMesh->mNormals[i]);
			const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0)
											? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;

			Vertex v(Vector3(pPos->x, pPos->y, pPos->z)
					, Vector2(pTexCoord->x, pTexCoord->y)
					, Vector3(pNormal->x, pNormal->y, pNormal->z));
			vertices.push_back(v);
		}

		for (unsigned int i = 0; i < paiMesh->mNumFaces; ++i) {
			const aiFace& face = paiMesh->mFaces[i];
			assert(face.mNumIndices == 3); //double check postprocessing triangulated properly
			indices.push_back(face.mIndices[0]);
			indices.push_back(face.mIndices[1]);
			indices.push_back(face.mIndices[2]);
		}

		submeshes[Index].Init(vertices, indices);
	}

	bool Mesh::InitMaterials(const aiScene* pScene, const string& filename) {
		
		// Extract the directory part from the file name
		std::string::size_type SlashIndex = filename.find_last_of("/");
		std::string Dir;

		if (SlashIndex == std::string::npos) {
			Dir = ".";
		}
		else if (SlashIndex == 0) {
			Dir = "/";
		}
		else {
			Dir = filename.substr(0, SlashIndex);
		}

		Vector3 test = Vector3::Zero;
		
		bool ret = true;
		for (unsigned int i = 0; i < pScene->mNumMaterials; ++i) {
			const aiMaterial* pMaterial = pScene->mMaterials[i];

			textures[i] = nullptr;
			if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
				aiString Path(filename);

				if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
					string FullPath = Dir + "/" + Path.data;
					textures[i] = new sf::Texture();
					//FullPath = "Assets/phoenix.png";
					if (!textures[i]->loadFromFile(FullPath))
						LOG_TRACE("Error loading texture {}", FullPath);
					delete textures[i];
					textures[i] = nullptr;
					ret = false;
				}
				else {
					printf("Loaded texture '%s'\n", filename.c_str());
				}
			}
			// Load a white texture in case the model does not include its own texture
			if (!textures[i]) {
				textures[i] = new sf::Texture();

				ret = textures[i]->loadFromFile("Assets/FlakTurret_Colour.png");
			}
		}
		return ret;

	}

	void Mesh::Render() {
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		for (unsigned int i = 0; i < submeshes.size(); ++i) {
			glBindBuffer(GL_ARRAY_BUFFER, submeshes[i].VB);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, submeshes[i].IB);

			const unsigned int MaterialIndex = submeshes[i].materialIndex;

			if (MaterialIndex < textures.size() && textures[MaterialIndex]) {
				//textures[MaterialIndex]->bind(GL_TEXTURE0);
				sf::Texture::bind(textures[MaterialIndex]);
			}
			//LOG_DEBUG("Rendering elements");
			glDrawElements(GL_TRIANGLES, submeshes[i].numIndices, GL_UNSIGNED_INT, 0);
			//glDrawArrays(GL_TRIANGLES, 0, submeshes[i].numIndices);
		}

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
	}

	void Mesh::Clear() {
		for (unsigned int i = 0; i < textures.size(); ++i)
			delete(textures[i]);
	}

	Mesh::SubMesh::SubMesh() {
		VB = INVALID_OGL_VALUE;
		IB = INVALID_OGL_VALUE;
		numIndices = 0;
		materialIndex = INVALID_MATERIAL;
	}

	Mesh::SubMesh::~SubMesh() {
		if (VB != INVALID_OGL_VALUE)
		glDeleteBuffers(1, &VB);
		if (IB != INVALID_OGL_VALUE)
		glDeleteBuffers(1, &IB);
	}

	void Mesh::SubMesh::Init(const vector<Vertex>& vertices, const vector<unsigned>& indices) {
		numIndices = indices.size();

		glGenBuffers(1, &VB);
		glBindBuffer(GL_ARRAY_BUFFER, VB);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

		glGenBuffers(1, &IB);
		glBindBuffer(GL_ARRAY_BUFFER, IB);
		glBufferData(GL_ARRAY_BUFFER, sizeof(unsigned int) * numIndices, &indices[0], GL_STATIC_DRAW);
	}
}
