#pragma once

#include <GL/glew.h>
#include <SFML/Graphics/Texture.hpp>
#include "Source/Core/assets/models/Mesh.h"

namespace sf {
	class Clock;
}

namespace Zen
{
	class Renderer3D
	{
	public:
		Renderer3D();
		~Renderer3D();

		GLuint vertexbuffer, colorbuffer, uvBuffer, spiderTexHandle;
		void LoadShaders();
		void OpenGLInit();
		
		void Init();
		void CreateTransform();
		void DrawRotatingCube(sf::Clock &clock);
		void Render();

		GLuint programID, matrixID;
		GLuint VertexArrayID;
		GLuint texture, textureID;
		mat4 MVP;
		sf::Image spiderTex;
		Mesh* pMesh;
		void SetProgramID(GLuint id);

		//static const GLfloat g_vertex_buffer_data[];
		//static const GLfloat g_vertex_buffer_dataTriangle[];
		//static const GLfloat g_color_buffer_data[];
	};

}
