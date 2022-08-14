#version 330 core

layout (location = 0) in vec2 position;

uniform mat4 MVP;

void main()
{
	float aspect = 800.0f / 600.0f;
	gl_Position = MVP * vec4(position.x, position.y, 0.0f, 1.0f);
}