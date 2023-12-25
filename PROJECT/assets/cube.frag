#version 430 core

in vec3 fragColor; // Input color from vertex shader

out vec4 finalColor; // Output color to framebuffer

void main() {
    finalColor = vec4(fragColor, 1.0);
}
