#include "cScene.h"

#include "Player/cPlayer.h"
#include "Assets/Model/cModel.h"
#include "Assets/Sprite/cSprite.h"
#include "Assets/cAssetManager.h"
#include "Assets/Camera/cLight.h"

cScene::cScene( GLFWwindow* _window )
	: m_model( cAssetManager::GetR().spawn< cModel >( "Models/sponza.obj" ) )
	, m_sprite( cAssetManager::GetR().spawn< cSpriteSolid >() )
{
	cCamera::Init< cPlayer >();
	cCamera::Init< cLight >();
}

cScene::~cScene()
{
	//no manual removal of assets exists yet. it all gets handled by cAssetManager deconstructor
}

void cScene::Update( double _deltatime, const math::sVector2i& _screenSize )
{
	m_sprite->m_size = { 256.0f, 256.0f };
	m_sprite->m_pos = m_sprite->m_size + math::sVector2f{ 8.0f, 8.0f } - math::sVector2f{ ( float )_screenSize.x, ( float )_screenSize.y } * 0.5f;

	cCamera::GetMainCamera< cPlayer >()->Update( _deltatime, _screenSize.x, _screenSize.y );
}
