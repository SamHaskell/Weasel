#version 410 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec3 a_Color;
layout(location = 3) in vec2 a_TexCoord;

uniform mat4 u_WorldToClipSpace;
uniform mat4 u_ModelToWorldSpace;

out vec4 v_Color;

void main() {
    gl_Position = u_WorldToClipSpace * u_ModelToWorldSpace * vec4(a_Position, 1.0);
    v_Color = vec4(a_Normal, 1.0);
}