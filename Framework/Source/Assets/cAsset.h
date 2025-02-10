#pragma once

#include "cAssetRenderer.h"

#include "iAsset.h"

template < class t >
class cAsset : iAsset
{
public:
    void draw() override
    {
        cAssetRenderer< t >::getRenderer()->draw( ( t* )this );
    }

    float m_priority = 0.0f;
};
