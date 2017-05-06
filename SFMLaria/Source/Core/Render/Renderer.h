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

		GLuint vertexbuffer, colorbuffer;
		void LoadShaders();
		void OpenGLInit();
		void Init();
		void CreateColorBuffer();
		void CreateTriangleBuffer();
		void CreateCubeBuffer();
		void CreateTransform();
		void DrawRotatingCube(sf::Clock &clock);
		void DrawTriangle();
		void DrawCube();
		void Render();

		GLuint programID, matrixID;
		mat4 MVP;
		void SetProgramID(GLuint id);

		//static const GLfloat g_vertex_buffer_data[];
		//static const GLfloat g_vertex_buffer_dataTriangle[];
		//static const GLfloat g_color_buffer_data[];
	};

}
