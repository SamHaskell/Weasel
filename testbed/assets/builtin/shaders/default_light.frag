#version 410 core

out vec4 f_Color;

uniform vec3 u_ObjectColor;

void main() {
    f_Color = vec4(u_ObjectColor, 1.0);
}