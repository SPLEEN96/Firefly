#version 330 core
uniform vec3 u_color;

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_color;

out vec3 v_color;

void main() {
    gl_Position = vec4(a_position.xyz, 1.f);
    v_color     = a_color;
}
