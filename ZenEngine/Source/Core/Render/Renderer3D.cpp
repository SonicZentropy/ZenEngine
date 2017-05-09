#include "stdafx.h"
#include "Renderer3D.h"
#include <SFML/System/Clock.hpp>
#include "Source/Core/Render/shader/ShaderManager.h"
#include "Source/Core/assets/manager/AssetLoader.h"
#include <SFML/Graphics/Texture.hpp>

namespace Zen
{
	const GLfloat g_vertex_buffer_dataTriangle[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};
	// Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
	static const GLfloat g_vertex_buffer_data[] = {
		-0.5f,-0.5f,-0.5f, // triangle 1 : begin
		-0.5f,-0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f, // triangle 1 : end
		0.5f, 0.5f,-0.5f, // triangle 2 : begin
		-0.5f,-0.5f,-0.5f,
		-0.5f, 0.5f,-0.5f, // triangle 2 : end
		0.5f,-0.5f, 0.5f,
		-0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.5f, 0.5f,-0.5f,
		0.5f,-0.5f,-0.5f,
		-0.5f,-0.5f,-0.5f,
		-0.5f,-0.5f,-0.5f,
		-0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f,-0.5f,
		0.5f,-0.5f, 0.5f,
		-0.5f,-0.5f, 0.5f,
		-0.5f,-0.5f,-0.5f,
		-0.5f, 0.5f, 0.5f,
		-0.5f,-0.5f, 0.5f,
		0.5f,-0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f,-0.5f,-0.5f,
		0.5f, 0.5f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f,-0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f, 0.5f,-0.5f,
		-0.5f, 0.5f,-0.5f,
		0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f,-0.5f,
		-0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,
		0.5f,-0.5f, 0.5f
	};

	static const GLfloat g_color_buffer_data[] = {
		0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,
		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,
		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f,
		0.279f,  0.317f,  0.505f,
		0.167f,  0.620f,  0.077f,
		0.347f,  0.857f,  0.137f,
		0.055f,  0.953f,  0.042f,
		0.714f,  0.505f,  0.345f,
		0.783f,  0.290f,  0.734f,
		0.722f,  0.645f,  0.174f,
		0.302f,  0.455f,  0.848f,
		0.225f,  0.587f,  0.040f,
		0.517f,  0.713f,  0.338f,
		0.053f,  0.959f,  0.120f,
		0.393f,  0.621f,  0.362f,
		0.673f,  0.211f,  0.457f,
		0.820f,  0.883f,  0.371f,
		0.982f,  0.099f,  0.879f
	};

	static const GLfloat g_uv_buffer_data[] = {
		0.000059f, 1.0f - 0.000004f,
		0.000103f, 1.0f - 0.336048f,
		0.335973f, 1.0f - 0.335903f,
		1.000023f, 1.0f - 0.000013f,
		0.667979f, 1.0f - 0.335851f,
		0.999958f, 1.0f - 0.336064f,
		0.667979f, 1.0f - 0.335851f,
		0.336024f, 1.0f - 0.671877f,
		0.667969f, 1.0f - 0.671889f,
		1.000023f, 1.0f - 0.000013f,
		0.668104f, 1.0f - 0.000013f,
		0.667979f, 1.0f - 0.335851f,
		0.000059f, 1.0f - 0.000004f,
		0.335973f, 1.0f - 0.335903f,
		0.336098f, 1.0f - 0.000071f,
		0.667979f, 1.0f - 0.335851f,
		0.335973f, 1.0f - 0.335903f,
		0.336024f, 1.0f - 0.671877f,
		1.000004f, 1.0f - 0.671847f,
		0.999958f, 1.0f - 0.336064f,
		0.667979f, 1.0f - 0.335851f,
		0.668104f, 1.0f - 0.000013f,
		0.335973f, 1.0f - 0.335903f,
		0.667979f, 1.0f - 0.335851f,
		0.335973f, 1.0f - 0.335903f,
		0.668104f, 1.0f - 0.000013f,
		0.336098f, 1.0f - 0.000071f,
		0.000103f, 1.0f - 0.336048f,
		0.000004f, 1.0f - 0.671870f,
		0.336024f, 1.0f - 0.671877f,
		0.000103f, 1.0f - 0.336048f,
		0.336024f, 1.0f - 0.671877f,
		0.335973f, 1.0f - 0.335903f,
		0.667969f, 1.0f - 0.671889f,
		1.000004f, 1.0f - 0.671847f,
		0.667979f, 1.0f - 0.335851f
	};

	Renderer3D::Renderer3D()
		: vertexbuffer(), colorbuffer{0}, uvBuffer{0}, programID{0}, matrixID{0}, VertexArrayID{0}, texture{0}, textureID{0} { }

	Renderer3D::~Renderer3D()
	{
		glDeleteBuffers(1, &vertexbuffer);
		glDeleteBuffers(1, &colorbuffer);
		glDeleteProgram(programID);
		glDeleteVertexArrays(1, &VertexArrayID);

	}


	void Renderer3D::Init() {
		//LoadShaders();
		OpenGLInit();
		//spider = AssetLoader::LoadOBJ("Assets/spider.obj");
		//CreateSpiderBuffer();
		//CreateSpiderUV();
		//CreateSpiderTexture();
		//CreateCubeBuffer();
		//CreateColorBuffer();
		//CreateTextureUV();
		pMesh = new Mesh();
		pMesh->LoadMesh("Assets/FlakTurretLP.obj");
		SetProgramID(programID);
	}



	void Renderer3D::LoadShaders()
	{
		programID = ShaderManager::LoadShaders(
			"D:/Workspace/Cpp/SFMLaria/SFMLaria/Source/Core/Render/shader/HoloVertexShader.vert",
			"D:/Workspace/Cpp/SFMLaria/SFMLaria/Source/Core/Render/shader/HoloFragmentShader.frag");
	}

	void Renderer3D::OpenGLInit()
	{

		//glClearDepth(1.f);
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

		// Enable Z-buffer read and write
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		//for transparent rendering, put in that part of render pipeline
		//Transparency is best implemented using blend function(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) with primitives sorted from farthest to nearest.Note that this transparency calculation does not require the presence of alpha bitplanes in the frame buffer.
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBlendFunc(GL_ONE, GL_ZERO);
		//glDepthMask(GL_TRUE);
		glDepthFunc(GL_LESS); //accept frag if closer to camera than former

		
		glGenVertexArrays(1, &VertexArrayID);
		glBindVertexArray(VertexArrayID);

		LoadShaders();

		matrixID = glGetUniformLocation(programID, "MVP"); //get handle for MVP uniform

		//proj matrix 45FoV 4:3
		mat4 projection = perspective(radians(45.0f), 4.0f / 3.0f, 0.1f, 500.0f);
		mat4 view = lookAt(
			vec3(4, 3, -5),
			vec3(0, 0, 0),
			vec3(0, 1, 0)
		);
		mat4 model = mat4(1.0f);
		MVP = projection * view * model;
		LOG_DEBUG("Made MVP");
		// Setup a perspective projection
		//glMatrixMode(GL_PROJECTION);
		//glLoadIdentity();
		//gluPerspective(90.f, 1.f, 1.f, 500.f);
	}


	

	void Renderer3D::CreateTransform() {
		// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
		glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)800/600, 0.1f, 100.0f);

		// Or, for an ortho camera :
		//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

		// Camera3D matrix
		glm::mat4 View = lookAt(
			glm::vec3(4, 3, 3), // Camera3D is at (4,3,3), in World Space
			glm::vec3(0, 0, 0), // and looks at the origin
			glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);

		// Model matrix : an identity matrix (model will be at the origin)
		glm::mat4 Model = glm::mat4(1.0f);
		// Our ModelViewProjection : multiplication of our 3 matrices
		glm::mat4 mvp = Projection * View * Model; // Remember, matrix multiplication is th
		GLuint MatrixID = glGetUniformLocation(0, "MVP");
	}

	void Renderer3D::DrawRotatingCube(sf::Clock& clock)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0.f, 0.f, -200.f);
		glRotatef(clock.getElapsedTime().asSeconds() * 50, 1.f, 0.f, 0.f);
		glRotatef(clock.getElapsedTime().asSeconds() * 30, 0.f, 1.f, 0.f);
		glRotatef(clock.getElapsedTime().asSeconds() * 90, 0.f, 0.f, 1.f);
		glBegin(GL_QUADS);

		glVertex3f(-50.f, -50.f, -50.f);
		glVertex3f(-50.f, 50.f, -50.f);
		glVertex3f(50.f, 50.f, -50.f);
		glVertex3f(50.f, -50.f, -50.f);

		glVertex3f(-50.f, -50.f, 50.f);
		glVertex3f(-50.f, 50.f, 50.f);
		glVertex3f(50.f, 50.f, 50.f);
		glVertex3f(50.f, -50.f, 50.f);

		glVertex3f(-50.f, -50.f, -50.f);
		glVertex3f(-50.f, 50.f, -50.f);
		glVertex3f(-50.f, 50.f, 50.f);
		glVertex3f(-50.f, -50.f, 50.f);

		glVertex3f(50.f, -50.f, -50.f);
		glVertex3f(50.f, 50.f, -50.f);
		glVertex3f(50.f, 50.f, 50.f);
		glVertex3f(50.f, -50.f, 50.f);

		glVertex3f(-50.f, -50.f, 50.f);
		glVertex3f(-50.f, -50.f, -50.f);
		glVertex3f(50.f, -50.f, -50.f);
		glVertex3f(50.f, -50.f, 50.f);

		glVertex3f(-50.f, 50.f, 50.f);
		glVertex3f(-50.f, 50.f, -50.f);
		glVertex3f(50.f, 50.f, -50.f);
		glVertex3f(50.f, 50.f, 50.f);

		glEnd();
	}
	
/*	void Renderer3D::DrawTriangle()
	{
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			static_cast<void*>(0)            // array buffer offset
		);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);
	}

	void Renderer3D::DrawCube() {
		static float clockTime = 0.1f;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0.f, 0.f, -200.f);
		glRotatef(clockTime * 50, 1.f, 0.f, 0.f);
		glRotatef(clockTime * 30, 0.f, 1.f, 0.f);
		glRotatef(clockTime * 90, 0.f, 0.f, 1.f);
		clockTime += 0.1f;

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			static_cast<void*>(0)            // array buffer offset
		);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		//glMatrixMode(GL_MODELVIEW);
		//glLoadIdentity();
		//glTranslatef(0.f, 0.f, -200.f);

		glDrawArrays(GL_TRIANGLES, 0, 12*3);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}*/

/*	void Renderer3D::DrawUVCube() {
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		// Set our "myTextureSampler" sampler to user Texture Unit 0
		glUniform1i(textureID, 0);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			2,                                // size : U+V => 2
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // 12*3 indices starting at 0 -> 12 triangles

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}*/

	

	void Renderer3D::Render() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(programID);

		glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);



		//DrawSpider();
		pMesh->Render();
	}

	void Renderer3D::SetProgramID(GLuint id) {
		glUseProgram(id);
	}


}
