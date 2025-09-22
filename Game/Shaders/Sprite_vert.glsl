#version 460 core

uniform vec2  u_pos;
uniform vec2  u_size;
uniform ivec2 u_screenSize;

out vec2 TexCoords;

void main()
{
    TexCoords.x = ( gl_VertexID % 2 );
    TexCoords.y = ( gl_VertexID / 2 );

    int x = ( gl_VertexID % 2 ) * 2 - 1;
    int y = ( gl_VertexID / 2 ) * 2 - 1;

    gl_Position = vec4( ( float( x ) * u_size.x + u_pos.x ) / float ( u_screenSize.x * 0.5f ), ( float( y ) * u_size.y + u_pos.y ) / float ( u_screenSize.y * 0.5f ), 0.0f, 1.0f);
}