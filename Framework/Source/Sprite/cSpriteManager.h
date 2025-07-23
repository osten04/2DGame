#pragma once

#include "Assets/cAssetRenderer.h"

class cSpriteManager : public cAssetRenderer< cSpriteManager >
{
private:
	unsigned int m_shaderProgram;

public:
	cSpriteManager();

	virtual void draw( iAsset* _sprite, math::sVector2i _screen ) override;
};


