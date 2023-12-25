#version 430 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor; // Color attribute

uniform mat4 model;
uniform mat4 view_projection;

out vec3 fragColor; // Output color to fragment shader

void main() {
    gl_Position = view_projection * model * vec4(aPos, 1.0);
    fragColor = aColor;
}
