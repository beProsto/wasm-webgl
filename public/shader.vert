#version 300 es
precision mediump float;

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Color;

out vec4 v_Color;

void main() {
	gl_Position = vec4(a_Position, 1.0f);
	v_Color = vec4(a_Color, 1.0f);
}