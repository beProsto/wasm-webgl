#version 300 es
precision mediump float;

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec2 a_TexCoord;
layout (location = 2) in vec3 a_Normal;

out vec4 v_Color;

uniform vec3 u_Offset;
uniform vec3 u_Size;

void main() {
	gl_Position = vec4(a_Position * u_Size + u_Offset, 1.0f);
	v_Color = vec4(a_TexCoord, 0.5f, 1.0f);
}