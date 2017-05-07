#pragma once

#include <GL/glew.h>

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

		GLuint vertexbuffer, colorbuffer, uvBuffer;
		void LoadShaders();
		void OpenGLInit();
		void CreateTextureUV();
		void Init();
		void CreateColorBuffer();
		void CreateTriangleBuffer();
		void CreateCubeBuffer();
		void CreateTransform();
		void DrawRotatingCube(sf::Clock &clock);
		void DrawTriangle();
		void DrawCube();
		void DrawUVCube();
		void Render();

		GLuint programID, matrixID;
		GLuint VertexArrayID;
		GLuint texture, textureID;
		mat4 MVP;
		void SetProgramID(GLuint id);

		//static const GLfloat g_vertex_buffer_data[];
		//static const GLfloat g_vertex_buffer_dataTriangle[];
		//static const GLfloat g_color_buffer_data[];
	};

}
