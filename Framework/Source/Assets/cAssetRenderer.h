#pragma once

#include "Singleton.hpp"

#include "iAsset.h"

template< class t >
class cAssetRenderer : public Singleton< t >
{
public:

    virtual void draw( iAsset* _asset ) = 0;
};
