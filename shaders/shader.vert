#version 400 core

layout (location = 0) in vec3 Position;

// uniform float u_scale;
uniform float u_time;
uniform mat4 u_transform;

void main() {
    gl_Position = u_transform * vec4(sin(u_time) * Position, 1.0);
}