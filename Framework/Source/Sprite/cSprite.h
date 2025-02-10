#include "Assets/cAsset.h"

#include "Math/Vector.h"

class cSpriteSolid : cAsset< cSpriteSolid >
{
public:
    math::sVector2f m_pos;
    math::sVector4f m_color;
};
