#include "cPlayer.h"

#include <algorithm>

#include <glm/gtc/quaternion.hpp>

cPlayer::cPlayer()
	: Super( true )
{
	m_rot.y = 270.0;
}

void cPlayer::Update( float _deltaTime, int _width, int _height )
{
	m_rot += glm::dvec3{ -m_mouseDelta.y, m_mouseDelta.x, 0.0 } * m_sens;
	m_rot.x  = std::clamp( m_rot.x, -90.0,  90.0 );

	glm::dvec3 movement = glm::dvec3{
		( double )( ( ( int )( bool )( m_inputMask & eInputMask::left    ) ) - ( ( int )( bool )( m_inputMask & eInputMask::right ) ) ), 
		0.0,
		( double )( ( ( int )( bool )( m_inputMask & eInputMask::forward ) ) - ( ( int )( bool )( m_inputMask & eInputMask::back  ) ) ) 
	};
	const glm::dvec3 forward = glm::dvec3{ cos( glm::radians( m_rot.y ) ), 0.0, sin( glm::radians( m_rot.y ) ) };
	const glm::dvec3 up      = glm::vec3( 0.0f, 1.0f, 0.0f );
	const glm::dvec3 right   = glm::cross( up, forward );

	movement = forward * movement.z + right * movement.x;

	movement.y = ( double )( ( ( int )( bool )( m_inputMask & eInputMask::up ) ) - ( ( int )( bool )( m_inputMask & eInputMask::down ) ) );

	m_pos += movement * m_speed * ( double )_deltaTime;

	m_mouseDelta = {};
	Super::Update( _deltaTime, _width, _height );
}

cPlayer::eInputMask cPlayer::getInputMask( int _key )
{
	switch ( _key )
	{
	case Input::KeyCode_W:         return forward;
	case Input::KeyCode_A:         return left;
	case Input::KeyCode_S:         return back;
	case Input::KeyCode_D:         return right;
	case Input::KeyCode_Space:     return up;
	case Input::KeyCode_LeftShift: return down;
	}
	return null;
}

void cPlayer::Input( const sInput& _input )
{
	switch ( _input.type )
	{
	case sInput::mouse:
		{
			const math::sVector2d& pos = _input.data.mouse.pos;

			const glm::dvec2 newPos = glm::dvec2( pos.x, pos.y );
			m_mouseDelta += ( newPos - m_lastFrameMousePos );
			m_lastFrameMousePos = newPos;
		}
		break;
	case sInput::keyboard:
		if ( _input.data.key.action == sInput::uData::sKey::press )
			m_inputMask |= getInputMask( _input.data.key.hexcode );
		else if( _input.data.key.action == sInput::uData::sKey::release )
			m_inputMask &= ~getInputMask( _input.data.key.hexcode );
		break;
	}
}
