#version 300 es
precision mediump float;

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec2 a_TexCoord;
layout (location = 2) in vec3 a_Normal;

out vec4 v_Color;

uniform vec3 u_Offset;
uniform vec3 u_Size;
uniform float u_Aspect;

void main() {
	vec3 offset = u_Offset;
	offset.y = u_Offset.y / u_Aspect;

	gl_Position = vec4(a_Position * u_Size + offset, 1.0f);
	gl_Position.y = gl_Position.y * u_Aspect;
	
	v_Color = vec4(a_TexCoord, 0.5f, 1.0f);
}