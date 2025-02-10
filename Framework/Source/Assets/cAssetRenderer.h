#pragma once

#include "Singleton.hpp"

#include "iAsset.h"

template< class t >
class cAssetRenderer : public Singleton< cAssetRenderer< t > >
{
protected: friend Singleton< cAssetRenderer< t > >;
    cAssetRenderer( void )
    {
        static_assert( std::is_base_of_v< iAsset, t >, "t must derive from cAsset");
    }

public:
    virtual void draw( t* ) = 0;

    static cAssetRenderer* getRenderer()
    {
        return cAssetRenderer::Get();
    }
};
