#version 330 core

in vec2 fTexCoords;
out vec4 color;

uniform sampler2D u_Texture;

void main()
{
	vec4 texColor = texture(u_Texture, fTexCoords);
	color = texColor;
} 