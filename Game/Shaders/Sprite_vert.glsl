#version 460 core

uniform vec2  u_pos;
uniform vec2  u_size;
uniform ivec2 u_screenSize;

void main()
{
    int x = ( gl_VertexID % 2 );
    int y = ( gl_VertexID / 2 );

    gl_Position = vec4( ( float( x ) * 0.5f * u_size.x + u_pos.x ) / float ( u_screenSize.x ), ( float( y ) * 0.5f * u_size.y + u_pos.y ) / float ( u_screenSize.y ), 0.0f, 1.0f);
}