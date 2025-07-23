#pragma once

#include "cAssetRenderer.h"

#include "iAsset.h"

template< class t >
class cAsset : public iAsset
{
private:
public:
    void draw()
    {
        cAssetRenderer< t >::GetR().draw( this );
    }

    float m_priority = 0.0f;
};
