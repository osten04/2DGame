#pragma once

#include "Assets/cAssetRenderer.h"
#include "Assets/cAssetManager.h"

class cSpriteManager : public cAssetRenderer< cSpriteManager >
{
public:
	cSpriteManager();

	virtual void draw( iAsset* _sprite, math::sVector2i _screen ) override;
};

RegisterAssetManager( cSpriteManager );
