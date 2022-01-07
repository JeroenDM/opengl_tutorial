#version 400 core

layout (location = 0) in vec3 Position;

// uniform float u_scale;
uniform float u_time;

void main() {
    gl_Position = vec4(sin(u_time) * Position, 1.0);
}