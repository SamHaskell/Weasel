#version 410 core

layout(location = 0) in vec3 a_Position;

uniform mat4 u_WorldToClipSpace;
uniform mat4 u_ModelToWorldSpace;

void main() {
    gl_Position = u_WorldToClipSpace * u_ModelToWorldSpace * vec4(a_Position, 1.0);
}