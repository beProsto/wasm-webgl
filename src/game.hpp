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

const char* vsc = 
"#version 300 es\n\
precision mediump float;\n\
\n\
layout (location = 0) in vec3 a_Position;\n\
layout (location = 1) in vec3 a_Color;\n\
\n\
out vec4 v_Color;\n\
\n\
void main() {\n\
\tgl_Position = vec4(a_Position, 1.0f);\n\
\tv_Color = vec4(a_Color, 1.0f);\n\
}\n";

const char* fsc = 
"#version 300 es\n\
precision mediump float;\n\
\n\
out vec4 o_Color;\n\
\n\
in vec4 v_Color;\n\
\n\
void main() {\n\
\to_Color = v_Color;\n\
}\n";

class Game {
public:
	Game():
	m_Shader(vsc, fsc),
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