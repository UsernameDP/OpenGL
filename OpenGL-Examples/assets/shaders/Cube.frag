#version 330 core

in vec2 fTexCoords;

out vec4 color;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	vec4 texColor1 = texture(texture1, fTexCoords);
	vec4 texColor2 = texture(texture2, fTexCoords);
	
	color =  texColor2;
} 