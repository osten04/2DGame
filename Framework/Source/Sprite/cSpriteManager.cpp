#include "cSpriteManager.h"

#include "FileLoaders/ShaderLoader.h"

cSpriteManager::cSpriteManager()
    : m_shaderProgram( glCreateProgram() )
{
    unsigned int vertexShader   = loadShader( "Shaders/Sprite_vert.glsl", GL_VERTEX_SHADER );
    unsigned int fragmentShader = loadShader( "Shaders/Sprite_frag.glsl", GL_FRAGMENT_SHADER );
    glAttachShader( m_shaderProgram, vertexShader );
    glAttachShader( m_shaderProgram, fragmentShader );
    glLinkProgram( m_shaderProgram );

    glDeleteShader( vertexShader );
    glDeleteShader( fragmentShader );

    m_colorUniformLocation = glGetUniformLocation( m_shaderProgram, "u_colour" );
    m_posUniformLocation  = glGetUniformLocation( m_shaderProgram, "u_pos" );
}

void cSpriteManager::draw( cSpriteSolid* _sprite )
{
    const cSpriteSolid& sprite = *( cSpriteSolid* )_sprite;
    const math::sVector2f& pos = sprite.m_pos;
    const math::sVector4f& col = sprite.m_color;

    glUseProgram( m_shaderProgram );
    glUniform4f( m_colorUniformLocation, col.x, col.y, col.z, col.w );
    glUniform2f( m_posUniformLocation, pos.x, pos.y );
    glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );

}
