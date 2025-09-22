#version 460 core

layout ( location = 0 ) out vec3 gPosition;
layout ( location = 1 ) out vec3 gNormal;
layout ( location = 2 ) out vec2 gUV;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;
uniform mat4 u_lightSpace;

smooth out vec3 FragPos;
smooth out vec3 Normal;
smooth out vec2 TexCoords;
smooth out vec4 FragPosLightSpace;

void main()
{
    FragPos = vec3( u_model * vec4( gPosition, 1.0f ) );
    Normal = transpose( inverse( mat3( u_model ) ) ) * gNormal;
    TexCoords = gUV;
    FragPosLightSpace = u_lightSpace * vec4( FragPos, 1.0f );

    gl_Position = u_projection * u_view * u_model * vec4( FragPos, 1.0f );
}