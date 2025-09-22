#pragma once

#include "Default.h"

#include "Assets/cAssetRenderer.h"
#include "Assets/cAssetManager.h"

class cModelManager : public SUPER( cAssetRenderer< cModelManager > )
{
public:
	cModelManager();
	~cModelManager();

	virtual void drawShadows( iAsset* _asset, math::sVector2i _screen ) override;
	virtual void draw       ( iAsset* _asset, math::sVector2i _screen ) override;
};

RegisterAssetManager( cModelManager );