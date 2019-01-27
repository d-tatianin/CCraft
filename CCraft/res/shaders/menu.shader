//A set of vertex and fragment shaders to render the game menu


#shader vertex

#version 330 core

layout (location = 0) in vec3 position;

uniform vec3 color;
uniform mat4 menuMat;

out vec4 buttonColor;

void main()
{
	buttonColor = vec4(color, 1.0f);
	gl_Position = menuMat * vec4(position, 1.0f);
}

#shader fragment

#version 330 core

in vec4 buttonColor;
out vec4 color;

void main()
{
	color = buttonColor;
}