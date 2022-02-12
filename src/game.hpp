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
		u_Aspect = glGetUniformLocation(m_Shader.getID(), "u_Aspect");

		cout << "Uniforms gotten:\nu_Offset = " << u_Offset << "\nu_Size = " << u_Size << "\nu_Aspect = " << u_Aspect << endl;

	}

	void update(float time) {
		float sinusoid = (sin(time / 500.0f) + 1.0) / 2.0;
		glClearColor(sinusoid, sinusoid, sinusoid, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUniform1f(u_Aspect, get_width() / get_height());

		// cout << "x: " << get_mouse_position_x() << " / " << get_width() << "  ||  " << "y: " << get_mouse_position_y() << " / " << get_height() << endl;
		// for(uint32_t mouseId = 0; mouseId < get_mouse_ammount(); mouseId++) {
		// 	float x, y;
			
		// 	x = get_mouse_position_x(mouseId) / get_width() * 2.0f - 1.0f;
		// 	y = get_mouse_position_y(mouseId) / get_height() * 2.0f - 1.0f;
		// 	y = -y; // inverse y

		// 	glUniform3f(u_Offset, x, y, 0.0f);
		// 	glDrawArrays(GL_TRIANGLES, 0, 3);
		// }
		uint32_t mouseId;
		// left side of the screen - a circle
		if(get_mouse_id_in_area(mouseId, Circle{get_width() / 6.0f, get_height() / 2.0f, get_height()/4.0f})) {
			float x, y;
			
			x = get_mouse_position_x(mouseId) / get_width() * 2.0f - 1.0f;
			y = get_mouse_position_y(mouseId) / get_height() * 2.0f - 1.0f;
			y = -y; // inverse y

			glUniform3f(u_Size, 0.2f, 0.2f, 0.0f);
			glUniform3f(u_Offset, x, y, 0.0f);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		// right side of the screen - an Axis Aligned Bounding Box
		if(get_mouse_id_in_area(mouseId, AABB{get_width() / 2.0f, 0.0f, get_width() / 2.0f, get_height()})) {
			float x, y;
			
			x = get_mouse_position_x(mouseId) / get_width() * 2.0f - 1.0f;
			y = get_mouse_position_y(mouseId) / get_height() * 2.0f - 1.0f;
			y = -y; // inverse y

			glUniform3f(u_Size, 0.5f, 0.5f, 0.0f);
			glUniform3f(u_Offset, x, y, 0.0f);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
	}

private:
	Shader m_Shader;
	VertexBuffer m_VertexBuffer;
	int u_Offset, u_Size, u_Aspect;
};