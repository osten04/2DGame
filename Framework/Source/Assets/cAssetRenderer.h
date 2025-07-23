#pragma once

#include "Singleton.hpp"

#include "iAsset.h"

template< class t >
class cAssetRenderer : public Singleton< t >
{
public:

    virtual void draw( iAsset* _sprite, math::sVector2i _screen ) = 0;
};
