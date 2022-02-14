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
uint32_t g_Music;

class Game {
public:
	Game():
	m_Shader(g_VertexShaderSource, g_FragmentShaderSource),
	m_VertexBuffer(vertices, sizeof(vertices))
	{
		m_Shader.bind();
		m_VertexBuffer.bind();

		u_Offset = glGetUniformLocation(m_Shader.getID(), "u_Offset");
		u_Size = glGetUniformLocation(m_Shader.getID(), "u_Size");
		u_Aspect = glGetUniformLocation(m_Shader.getID(), "u_Aspect");

		cout << "Uniforms gotten:\nu_Offset = " << u_Offset << "\nu_Size = " << u_Size << "\nu_Aspect = " << u_Aspect << endl;
	}
	~Game() {}

	void start() {
		play_audio(g_Music);
	}

	void update(float time) {
		float sinusoid = (sin(time / 500.0f) + 1.0) / 2.0;
		glClearColor(sinusoid, sinusoid, sinusoid, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		const float width = get_width();
		const float height = get_height();

		glUniform1f(u_Aspect, width / height);

		// cout << "x: " << get_mouse_position_x() << " / " << width << "  ||  " << "y: " << get_mouse_position_y() << " / " << height << endl;
		// for(uint32_t mouseId = 0; mouseId < get_mouse_ammount(); mouseId++) {
		// 	float x, y;
			
		// 	x = get_mouse_position_x(mouseId) / width * 2.0f - 1.0f;
		// 	y = get_mouse_position_y(mouseId) / height * 2.0f - 1.0f;
		// 	y = -y; // inverse y

		// 	glUniform3f(u_Offset, x, y, 0.0f);
		// 	glDrawArrays(GL_TRIANGLES, 0, 3);
		// }
		Mouse mouse;
		// left side of the screen - a circle
		if(get_mouse_in_area(mouse, Circle{width / 6.0f, height / 2.0f, height/4.0f})) {
			float x, y;

			if(is_mouse_button_pressed(0, mouse.id)) {
				play_audio(g_Music);
			}
			
			x = mouse.x / width * 2.0f - 1.0f;
			y = mouse.y / height * 2.0f - 1.0f;
			y = -y; // inverse y

			glUniform3f(u_Size, 0.2f, 0.2f, 0.0f);
			glUniform3f(u_Offset, x, y, 0.0f);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		// right side of the screen - an Axis Aligned Bounding Box
		if(get_mouse_in_area(mouse, Rect{width / 2.0f, 0.0f, width / 2.0f, height})) {
			float x, y;

			if(is_mouse_button_pressed(0, mouse.id)) {
				stop_audio(g_Music);
			}
			
			x = mouse.x / width * 2.0f - 1.0f;
			y = mouse.y / height * 2.0f - 1.0f;
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