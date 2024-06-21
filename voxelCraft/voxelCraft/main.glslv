#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;

out vec4 a_color;
out vec2 a_texCoord;

void main()
{
	gl_Position = vec4(position, 1.0f);
	a_color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	a_texCoord = texCoord;
}