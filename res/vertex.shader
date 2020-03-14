#version 420 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

out vec4 v_color;

void main() {
    v_color = vec4(color.r/255, color.g/255, color.b/255, color.a/255);
    gl_Position = position;
}