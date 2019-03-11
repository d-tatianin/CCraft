//A set of vertex and fragment shaders to render the in-game hud


#shader vertex

#version 330 core

layout(location = 0) in vec3 position;

uniform mat4 projection;
uniform mat4 scale;

void main()
{
	gl_Position = scale * projection * vec4(position, 1.0f);
}

#shader fragment

#version 330 core

uniform vec3 color;

out vec4 outColor;

void main()
{
	outColor = vec4(color, 1.0f);
}