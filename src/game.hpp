#pragma once

#include "utils/include/utils.hpp"

#include "shaders.hpp"
#include "vertexbuffers.hpp"

const Vertex vertices[] = {
	// Position                 // Tex Coords     // Normals
	{ Vec3{-0.5f, -0.5f, 0.0f}, Vec2{0.0f, 0.0f}, Vec3{0.0f, 0.0f, 1.0f} },
	{ Vec3{ 0.0f,  0.5f, 0.0f}, Vec2{0.5f, 1.0f}, Vec3{0.0f, 0.0f, 1.0f} },
	{ Vec3{ 0.5f, -0.5f, 0.0f}, Vec2{1.0f, 0.0f}, Vec3{0.0f, 0.0f, 1.0f} }
};

char* g_VertexShaderSource;
char* g_FragmentShaderSource;
unsigned char* g_TextureImageData;

class Game {
public:
	Game():
	m_Shader(g_VertexShaderSource, g_FragmentShaderSource),
	m_VertexBuffer(vertices, sizeof(vertices))
	{}
	~Game() {}

	void start() {
		m_Shader.bind();
		m_VertexBuffer.bind();

		u_Offset = glGetUniformLocation(m_Shader.getID(), "u_Offset");
		u_Size = glGetUniformLocation(m_Shader.getID(), "u_Size");

		cout << "Uniforms gotten:\nu_Offset = " << u_Offset << "\nu_Size = " << u_Size << endl; 
	}

	void update(float time) {
		float sinusoid = (sin(time / 500.0f) + 1.0) / 2.0;

		glUniform3f(u_Offset, 0.5f, 0.5f, 0.0f);
		glUniform3f(u_Size, 0.5f, 0.5f, 0.0f);

		glClearColor(sinusoid, sinusoid, sinusoid, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

private:
	Shader m_Shader;
	VertexBuffer m_VertexBuffer;
	int u_Offset, u_Size;
};