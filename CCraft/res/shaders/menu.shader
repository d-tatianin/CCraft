//A set of vertex and fragment shaders to render the game menu


#shader vertex

#version 330 core

layout (location = 0) in vec3 position;

uniform mat4 menuMat;

void main()
{
	gl_Position = menuMat * vec4(position, 1.0f);
}

#shader fragment

#version 330 core

out vec4 color;

void main()
{
	color = vec4(1.0f, 0.5f, 0.0f, 1.0f);
}