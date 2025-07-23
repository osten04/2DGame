#version 460 core

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
    int x = gl_VertexID % 2;
    int y = gl_VertexID / 2;

    vec4 pos = vec4( float( x ) * 0.5f, float( y ) * 0.5f, 0.0f, 1.0f );
    
    gl_Position = projection * view * model * pos;
}