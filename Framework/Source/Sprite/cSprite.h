#include "Assets/cAsset.h"

#include "Math/Vector.h"
#include "Sprite/cSpriteManager.h"

class cSpriteSolid : public cAsset< cSpriteManager >
{
public:
    math::sVector2f m_pos;
    math::sVector4f m_color;
};
