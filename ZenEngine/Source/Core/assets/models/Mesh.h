// // /**
// //  * Mesh.h
// //  * Dylan Bailey
// //  * 20170507
// // */

#pragma once
#include "Source/Core/assets/models/IRenderable.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include "Source/Core/util/Vertex.h"

#define INVALID_MATERIAL 0xFFFFFFFF
#define INVALID_OGL_VALUE 0xFFFFFFFF
struct aiMesh;
struct aiScene;

namespace Zen
{
	class Mesh : IRenderable
	{
	public:
		Mesh();
		~Mesh();
		bool LoadMesh(const string& filename, unsigned int processingFlags = 0);
		void Render();

	private:
		bool InitFromScene(const aiScene* pScene, const string& filename);
		void InitMesh(unsigned int Index, const aiMesh* paiMesh);
		bool InitMaterials(const aiScene* pScene, const string& filename);
		void Clear();

		struct SubMesh
		{
			SubMesh();
			~SubMesh();

			void Init(const vector<Vertex>& vertices, const vector<unsigned int>& indices);

			GLuint VB;
			GLuint IB;
			unsigned int numIndices;
			unsigned int materialIndex;
		};

		vector<SubMesh> submeshes;
		vector<sf::Texture*> textures;

	};
}
