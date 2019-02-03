#shader vertex

#version 330 core
layout(location = 0) in vec3 aPos;

uniform mat4 MVP;

void main()
{
	gl_Position = MVP * vec4(aPos, 1.0f);
}

#shader fragment

#version 330 core

uniform vec3 color;
out vec4 outColor;

void main()
{
	outColor = vec4(color, 1.0f);
}