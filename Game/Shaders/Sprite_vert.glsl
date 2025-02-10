#version 460 core

uniform vec4 u_pos;

void main()
{
    int x = gl_VertexID % 2;
    int y = gl_VertexID / 2;

    gl_Position = vec4( float( x ) * 0.5f, float( y ) * 0.5f, 0.0f, 1.0f);
}