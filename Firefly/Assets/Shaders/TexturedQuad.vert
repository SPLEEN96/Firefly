#version 330 core
uniform vec3 u_color;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_color;
layout(location = 2) in vec2 a_tex_coord;

out vec3 v_color;
out vec2 v_tex_coord;

void main() {
    gl_Position = projection * view * model * vec4(a_position.xyz, 1.f);
    v_color     = u_color;
    v_tex_coord = a_tex_coord;
}