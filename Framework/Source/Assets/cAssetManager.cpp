#include "cAssetManager.h"

const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
unsigned int depthMapFBO, depthMap;

#include <glad/glad.h>

cAssetManager::cAssetManager()
{
    for ( const ManagerInitiator& element : m_regestry )
    {
        element.init();
    }

    glGenFramebuffers(1, &depthMapFBO);

    glGenTextures( 1, &depthMap  );
    glBindTexture( GL_TEXTURE_2D, depthMap );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

    glBindFramebuffer( GL_FRAMEBUFFER, depthMapFBO );
    glFramebufferTexture2D( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0 );
    glDrawBuffer( GL_NONE );
    glReadBuffer( GL_NONE );
    glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}

cAssetManager::~cAssetManager()
{
    for ( const ManagerInitiator& element : m_regestry )
    {
        element.destroy();
    }
}

void cAssetManager::draw( math::sVector2i _screen )
{
    int frameBuffer;
    glGetIntegerv( GL_FRAMEBUFFER_BINDING, &frameBuffer );

    glViewport( 0, 0, SHADOW_WIDTH, SHADOW_HEIGHT );
    glBindFramebuffer( GL_FRAMEBUFFER, depthMapFBO );
    glClear( GL_DEPTH_BUFFER_BIT );

    for ( cSmartPtr< iAsset >& element : m_assets)
        element->drawShadows( _screen );

    glViewport( 0, 0, _screen.x, _screen.y );
    glBindFramebuffer( GL_FRAMEBUFFER, frameBuffer );
    glBindTexture( GL_TEXTURE_2D, depthMap );

    for ( auto& element : m_assets )
        element->draw( _screen );
}
