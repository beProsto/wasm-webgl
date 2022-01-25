#pragma once

#include "utils/include/utils.hpp"
#include "openlibm/include/openlibm.h"

#include "shaders.hpp"
#include "vertexbuffers.hpp"

const float vertices[] = {
	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
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
	Game() {}
	~Game() {}

	void start() {
		// initialising the webgl objects lol
		
		// create both shaders
		vShaderID = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vShaderID, vsc);
		glCompileShader(vShaderID);

		fShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fShaderID, fsc);
		glCompileShader(fShaderID);

		// make a program out of the shaders
		shaderID = glCreateProgram();
		glAttachShader(shaderID, vShaderID);
		glAttachShader(shaderID, fShaderID);
		glLinkProgram(shaderID);
		glValidateProgram(shaderID);

		// we don't need the shaders anymore
		// glDeleteShader(vShaderID);
		// glDeleteShader(fShaderID);

		glUseProgram(shaderID);

		// create a vertex array (vertex descriptor)
		vaID = glCreateVertexArray();
		glBindVertexArray(vaID);

		// create an array buffer (the actual vertex buffer)
		vbID = glCreateBuffer();
		glBindBuffer(GL_ARRAY_BUFFER, vbID);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 3 * sizeof(float));

		// pass data to the buffer
		glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), (void*)&vertices[0], GL_STATIC_DRAW);
	}
	void update() {
		m_ColorInterval += 0.01f;
		float sinusoid = (sin(m_ColorInterval) + 1.0) / 2.0;

		glClearColor(sinusoid, sinusoid, sinusoid, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// glUseProgram(shaderID);
		// glBindVertexArray(vaID);
		// glBindBuffer(GL_ARRAY_BUFFER, vbID);

		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

private:
	float m_ColorInterval;
	uint32_t vShaderID, fShaderID, shaderID, vbID, vaID;
};