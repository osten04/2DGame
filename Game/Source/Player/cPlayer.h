#pragma once

#include "Default.h"

#include "Assets/Camera/cCamera.h"

class cPlayer: public SUPER( cCamera )
{
public:
	cPlayer();

	virtual void Update( float _deltaTime, int _width, int _height ) override;

	virtual void Input( const sInput& _input ) override;
private:
	glm::dvec2 m_mouseDelta = glm::dvec2();

	glm::dvec2 m_lastFrameMousePos = glm::dvec2();
	
	const double m_sens  = 0.1;
	const double m_speed = 1024.0;

	enum eInputMask : char
	{
		null    = 0x00,
		forward = 0x01,
		left    = 0x02,
		back    = 0x04,
		right   = 0x08,
		up      = 0x10,
		down    = 0x20
	};

	char m_inputMask = null;

	eInputMask getInputMask( int _key );
};
