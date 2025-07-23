#include "cSpriteManager.h"
#include "Sprite/cSprite.h"

#include "glad/glad.h"

#include "FileLoaders/ShaderLoader.h"

cSpriteManager::cSpriteManager()
    : m_shaderProgram( glCreateProgram() )
{
    unsigned int vertexShader   = loadShader( "Shaders/Sprite_vert.glsl", GL_VERTEX_SHADER );
    unsigned int fragmentShader = loadShader( "Shaders/Sprite_frag.glsl", GL_FRAGMENT_SHADER );
    glAttachShader( m_shaderProgram, vertexShader );
    glAttachShader( m_shaderProgram, fragmentShader );
    glLinkProgram( m_shaderProgram );

    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader( vertexShader );
    glDeleteShader( fragmentShader );
}

void cSpriteManager::draw( iAsset* _sprite, math::sVector2i _screen )
{
    const cSpriteSolid& sprite = *( cSpriteSolid* )_sprite;
    const math::sVector2f& pos  = sprite.m_pos;
    const math::sVector2f& size = sprite.m_size;
    const math::sVector4f& col  = sprite.m_color;

    glUseProgram( m_shaderProgram );
    glUniform4f( glGetUniformLocation( m_shaderProgram, "u_colour" ), col.x, col.y, col.z, col.w );
    glUniform2f( glGetUniformLocation( m_shaderProgram, "u_pos"  ), pos.x, pos.y );
    glUniform2f( glGetUniformLocation( m_shaderProgram, "u_size" ), size.x, size.y );
    glUniform2i( glGetUniformLocation( m_shaderProgram, "u_screenSize" ), _screen.x, _screen.y );
    glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );

}
