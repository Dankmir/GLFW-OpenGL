#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 color;

out vec3 Color;

uniform mat4 u_MVP;

void main()
{
    Color = color;
    gl_Position = u_MVP * position;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 Color;

void main()
{
    color = vec4(Color, 1.0f);
};