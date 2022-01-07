#version 400 core

layout (location = 0) in vec3 Position;

void main() {
    gl_Position = vec4(0.5 * Position, 1.0);
}