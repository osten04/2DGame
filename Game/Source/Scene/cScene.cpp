#include "cScene.h"

#include "Assets/cAssetManager.h"
#include "Sprite/cSprite.h"

#include "Character/cCharacter.h"

cScene::cScene( GLFWwindow* _window )
	: m_character( new cCharacter() )
{

}

cScene::~cScene()
{
	delete m_character;
}

void cScene::Update( double _deltatime, const math::sVector2i& _screenSize )
{
	m_character->Update( _deltatime );
}
