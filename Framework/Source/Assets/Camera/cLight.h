#pragma once

#include "Default.h"
#include "cCamera.h"

class cLight : public SUPER( cCamera )
{
public:
	cLight();
	virtual void Update( float _deltaTime, int _width, int _height ) override;
};

