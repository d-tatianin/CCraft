#shader vertex

#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 inTexCoords;
layout(location = 2) in mat4 model;

out vec2 texCoords;

uniform mat4 view;
uniform mat4 projection;

void main()
{
	texCoords = inTexCoords;
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
}

#shader fragment

#version 330 core

in vec2 texCoords;
out vec4 outColor;

uniform sampler2D ourTex;

void main()
{
	outColor = texture(ourTex, texCoords);
}