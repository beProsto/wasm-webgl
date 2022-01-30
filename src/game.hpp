#pragma once

#include "utils/include/utils.hpp"
#include "openlibm/include/openlibm.h"

#include "shaders.hpp"
#include "vertexbuffers.hpp"

const Vertex vertices[] = {
	// Position               // Color
	Vec3{-0.5f, -0.5f, 0.0f}, Vec3{1.0f, 0.0f, 0.0f},
	Vec3{ 0.0f,  0.5f, 0.0f}, Vec3{0.0f, 1.0f, 0.0f},
	Vec3{ 0.5f, -0.5f, 0.0f}, Vec3{0.0f, 0.0f, 1.0f}
};

char* g_VertexShaderSource;
char* g_FragmentShaderSource;

class Game {
public:
	Game():
	m_Shader(g_VertexShaderSource, g_FragmentShaderSource),
	m_VertexBuffer(vertices),
	m_ColorInterval(0)
	{}
	~Game() {}

	void start() {
		m_Shader.bind();
		m_VertexBuffer.bind();
	}

	void update() {
		m_ColorInterval += 0.01f;
		float sinusoid = (sin(m_ColorInterval) + 1.0) / 2.0;

		glClearColor(sinusoid, sinusoid, sinusoid, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

private:
	Shader m_Shader;
	VertexBuffer m_VertexBuffer;
	float m_ColorInterval;
};