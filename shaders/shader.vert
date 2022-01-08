#version 400 core

layout (location = 0) in vec3 Position;

// uniform float u_scale;
uniform float u_time;
uniform mat4 u_transform;

out vec4 Color;

const vec4 colors[3] = vec4[3](
    vec4(1, 0, 0, 1),
    vec4(0, 1, 0, 1),
    vec4(0, 0, 1, 1)
);

void main() {
    gl_Position = u_transform * vec4(sin(u_time) * Position, 1.0);
    Color = colors[gl_VertexID];
}