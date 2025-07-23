#pragma once

#include "cAssetRenderer.h"

template< class t >
class cAsset : public iAsset
{
private:
public:
    void draw( math::sVector2i _screen )
    {
        cAssetRenderer< t >::GetR().draw( this, _screen );
    }

    float m_priority = 0.0f;
};
