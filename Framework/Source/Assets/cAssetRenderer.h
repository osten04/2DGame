#pragma once

#include "Singleton.hpp"

#include "iAsset.h"

template< class t >
class cAssetRenderer : public Singleton< cAssetRenderer< t > >
{
public:
    cAssetRenderer( )
    {
        static_assert( std::is_base_of_v< iAsset, t >, "t must derive from cAsset");
    }

    void draw( t* _asset );

    static cAssetRenderer* getRenderer()
    {
        return cAssetRenderer::Get();
    }
};
