#version 410 core

out vec4 f_Color;

in vec4 v_Color;

void main() {
    f_Color = v_Color;
}