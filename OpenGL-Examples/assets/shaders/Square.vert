#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 fTexCoords;

void main()
{
    fTexCoords = aTexCoords;

    gl_Position = vec4(aPos, 1.0, 1.0);
}