#include "cScene.h"

#include "Assets/cAssetManager.h"
#include "Sprite/cSprite.h"

cScene::cScene( GLFWwindow* _window )
	: m_sprite( cAssetManager::GetR().spawn< cSpriteSolid >() )
{
	m_sprite->m_color = { 1.0f, 1.0f, 1.0f, 1.0f };
	m_sprite->m_pos = { 0, 0 };
	m_sprite->m_size = { 320.0f, 320.0f };
}

cScene::~cScene()
{
}

void cScene::Update( double _deltatime, const math::sVector2i& _screenSize )
{
	m_time += _deltatime;

	m_sprite->m_pos.x = ( float )( cos( m_time ) * 128.0 );

	printf("%.6f\n", m_sprite->m_pos.x);
}
