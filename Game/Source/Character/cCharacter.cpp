#include "cCharacter.h"

#include "Input/cInputManager.h"
#include "Assets/cAssetManager.h"

cCharacter::cCharacter( )
	: m_binds( sKeyBinds{ .left = Input::KeyCode_A, .right = Input::KeyCode_D, .jump = Input::KeyCode_Space } )
	, m_sprite( cAssetManager::GetR().spawn< cSpriteSolid >() )
{
	m_sprite->m_color = { 1.0f, 1.0f, 1.0f, 1.0f };
	m_sprite->m_size  = { 512.0f, 512.0f };

	cInputManager::GetR().Subscribe( this, &cCharacter::Input );
}

cCharacter::~cCharacter()
{
	cInputManager::GetR().UnSubscribe( this );
}

void cCharacter::Update( double _deltaTime )
{
	m_vel.x = ( ( int )( ( m_input & right ) > 0 ) - ( int )( ( m_input & left ) > 0) ) * 8.0f;

	m_vel.y -= 9.82f * ( float )_deltaTime;

	if ( m_gounded && m_input & jump )
	{
		m_vel.y = 4.0f;
	}

	math::sVector2f& pos = m_sprite->m_pos;
	pos = pos + m_vel * 512.0f * ( float )_deltaTime;

	if ( pos.y < 0.0f )
	{
		m_vel.y = fmax( 0.0f, m_vel.y );
		pos.y = 0.0f;

		m_gounded = true;
	}
	else
		m_gounded = false;

	printf( "vel: x:%1.6f, y:%2.6f pos: x:%3.6f, y:%4.6f\n", m_vel.x, m_vel.y, pos.y, pos.y );

}

void cCharacter::Input( const sInput& _input )
{
	switch ( _input.type )
	{
		case sInput::keyboard: 
		{
			switch ( _input.data.key.action )
			{
				case sInput::uData::sKey::press:   m_input |= GetInputMask( _input.data.key.hexcode ); break;
				case sInput::uData::sKey::release: m_input ^= GetInputMask( _input.data.key.hexcode ); break;
			}
		}
	}
}

cCharacter::eInputsMask cCharacter::GetInputMask( int _input )
{
	if ( _input == m_binds.left  ) return eInputsMask::left;
	if ( _input == m_binds.right ) return eInputsMask::right;
	if ( _input == m_binds.jump  ) return eInputsMask::jump;

	return eInputsMask::none;
}
