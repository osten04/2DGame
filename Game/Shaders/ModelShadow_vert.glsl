#version 460 core

layout ( location = 0 ) in vec3 gPosition;
layout ( location = 1 ) in vec3 gNormal;
layout ( location = 2 ) in vec2 gUV;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

smooth out vec3 norm;

void main()
{
    gl_Position = u_projection * u_view * u_model * vec4( gPosition, 1.0f );
}