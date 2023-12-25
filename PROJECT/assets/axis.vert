#version 430 core

layout(location = 0) in vec3 aPos;

uniform mat4 view_projection;

out vec3 fragColor;

void main() {
    fragColor = aPos + 0.25;
    gl_Position = view_projection * vec4(aPos, 1.0);
}
