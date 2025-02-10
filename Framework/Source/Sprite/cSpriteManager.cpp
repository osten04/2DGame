#include "cSpriteManager.h"

#include "FileLoaders/ShaderLoader.h"

cSpriteManager::cSpriteManager()
    : m_shaderProgram( glCreateProgram() )
{
    unsigned int vertexShader   = loadShader( "", GL_VERTEX_SHADER );
    unsigned int fragmentShader = loadShader( "", GL_FRAGMENT_SHADER );
    glAttachShader( m_shaderProgram, vertexShader );
    glAttachShader( m_shaderProgram, fragmentShader );
    glLinkProgram( m_shaderProgram );

    glDeleteShader( vertexShader );
    glDeleteShader( fragmentShader );

    m_colorUniformLocation = glGetUniformLocation( m_shaderProgram, "u_colour" );

    glGenTextures( 1, &m_whiteTexture );

}

void cSpriteManager::draw( cSprite* _sprite )
{
    glUseProgram( m_shaderProgram );
    glUniform4f( m_colorUniformLocation, 0.0f, 0.0f, 0.0f, 0.0f );

    if( unsigned int texture = 0; texture )
        glBindTexture( 0, texture );
    else
    {
        glBindTexture( 0, m_whiteTexture );
    }
}

void cSpriteManager::setTexture( void )
{

}
