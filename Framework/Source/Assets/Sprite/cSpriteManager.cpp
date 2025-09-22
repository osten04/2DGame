#include "cSpriteManager.h"
#include "Assets/Sprite/cSprite.h"

#include "glad/glad.h"

#include "FileLoaders/ShaderLoader.h"

cSpriteManager::cSpriteManager()
    : cAssetRenderer( "Shaders/Sprite", nullptr )
{

}

void cSpriteManager::draw( iAsset* _sprite, math::sVector2i _screen )
{
    glDisable( GL_DEPTH_TEST );

    const cSpriteSolid& sprite = *static_cast < cSpriteSolid* >( _sprite );

    const math::sVector2f& pos  = sprite.m_pos;
    const math::sVector2f& size = sprite.m_size;
    const math::sVector4f& col  = sprite.m_color;

    glUseProgram( m_shaderProgram );
    glUniform4f( glGetUniformLocation( m_shaderProgram, "u_colour" ), col.x, col.y, col.z, col.w );
    glUniform2f( glGetUniformLocation( m_shaderProgram, "u_pos"  ), pos.x, pos.y );
    glUniform2f( glGetUniformLocation( m_shaderProgram, "u_size" ), size.x, size.y );
    glUniform2i( glGetUniformLocation( m_shaderProgram, "u_screenSize" ), _screen.x, _screen.y );
    glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );
    glUseProgram( 0 );
    glEnable( GL_DEPTH_TEST );
}