#pragma once

#include "utils/include/utils.hpp"

static uint32_t g_BoundShader;

class Shader {
public:
	Shader() {
		m_ID = glCreateProgram();
	}
	Shader(const char* _vertexShader, const char* _fragmentShader) {
		m_ID = glCreateProgram();
		compile(_vertexShader, _fragmentShader);
	}
	~Shader() {
		glDeleteProgram(m_ID);
	}

	void compile(const char* _vertexShader, const char* _fragmentShader) const {
		// create both shaders
		uint32_t vShaderID = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vShaderID, _vertexShader);
		glCompileShader(vShaderID);

		uint32_t fShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fShaderID, _fragmentShader);
		glCompileShader(fShaderID);

		// make a program out of the shaders
		glAttachShader(m_ID, vShaderID);
		glAttachShader(m_ID, fShaderID);
		glLinkProgram(m_ID);
		glValidateProgram(m_ID);

		// we don't need the shaders anymore
		glDeleteShader(vShaderID);
		glDeleteShader(fShaderID);

		bind();
	}

	void bind() const {
		if(g_BoundShader != m_ID) {
			g_BoundShader = m_ID;
			glUseProgram(m_ID);
		}
	}

private:
	uint32_t m_ID;
};