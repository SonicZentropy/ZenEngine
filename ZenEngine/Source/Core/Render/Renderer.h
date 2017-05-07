#pragma once

#include <GL/glew.h>
#include "Source/Core/assets/models/ObjModel.h"
#include <SFML/Graphics/Texture.hpp>
#include "Source/Core/assets/models/Mesh.h"

namespace sf {
	class Clock;
}

namespace Zen
{
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		GLuint vertexbuffer, colorbuffer, uvBuffer, spiderTexHandle;
		void LoadShaders();
		void OpenGLInit();
		void CreateTextureUV();
		void CreateSpiderBuffer();
		void CreateSpiderUV();
		void CreateSpiderTexture();
		void Init();
		void CreateColorBuffer();
		void CreateTriangleBuffer();
		void CreateCubeBuffer();
		void CreateTransform();
		void DrawRotatingCube(sf::Clock &clock);
		void DrawTriangle();
		void DrawCube();
		void DrawUVCube();
		void DrawSpider();
		void Render();

		GLuint programID, matrixID;
		GLuint VertexArrayID;
		GLuint texture, textureID;
		mat4 MVP;
		ObjModel spider;
		sf::Image spiderTex;
		Mesh* pMesh;
		void SetProgramID(GLuint id);

		//static const GLfloat g_vertex_buffer_data[];
		//static const GLfloat g_vertex_buffer_dataTriangle[];
		//static const GLfloat g_color_buffer_data[];
	};

}
