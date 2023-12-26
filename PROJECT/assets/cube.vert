#version 430 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor; // Color attribute

uniform mat4 VP;

out vec3 fragColor; // Output color to fragment shader

void main() {
    gl_Position = VP * vec4(aPos, 1.0);
    fragColor = aColor;
}
