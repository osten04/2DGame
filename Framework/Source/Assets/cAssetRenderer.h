#pragma once

#include "Singleton.hpp"

#include "iAsset.h"

class iAssetRenderer
{
protected:
    unsigned int m_shaderProgram, m_shadowShaderProgram;

public:
    static unsigned int CompileShader( const char* _shader );

    iAssetRenderer( const char* _shader, const char* _shadowShader );
    ~iAssetRenderer();
};

template< class t >
class cAssetRenderer : public Singleton< t >, public iAssetRenderer
{
public:
    virtual void drawShadows( iAsset* _Asset, math::sVector2i _screen ) { };
    virtual void draw( iAsset* _Asset, math::sVector2i _screen ) = 0;

    cAssetRenderer( const char* _shader, const char* _shadowShader ) : iAssetRenderer( _shader, _shadowShader ) {};
};
