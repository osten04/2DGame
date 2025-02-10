#include "cAssetRenderer.h"

#include "Sprite/cSpriteManager.h"


template<>
void cAssetRenderer< cSpriteSolid >::draw( cSpriteSolid* _asset )
{
	( ( cSpriteManager* ) this )->draw( _asset );
}