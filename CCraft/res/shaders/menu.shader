//A set of vertex and fragment shaders to render the game menu


#shader vertex

#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 inTexCoords;

out vec2 texCoords;

uniform mat4 menuMat;

void main()
{
	texCoords = inTexCoords;
	gl_Position = menuMat * vec4(position, 1.0f);
}

#shader fragment

#version 330 core

in vec2 texCoords;

uniform sampler2D texOne;
uniform vec3 color;

out vec4 outColor;

void main()
{
	outColor = texture(texOne, texCoords) * vec4(color, 1.0f);
}