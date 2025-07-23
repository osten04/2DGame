#pragma once

#include "Math/Vector.h"

class iAsset
{
public:
    virtual void draw( math::sVector2i _screen ) = 0;
};