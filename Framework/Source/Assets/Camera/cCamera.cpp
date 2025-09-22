#include "cCamera.h"

#include "Input/cInputManager.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_transform.hpp>

cCamera::cCamera( bool _input )
{
	if ( _input )
		cInputManager::GetR().Subscribe( this, &cCamera::Input );

	if ( !m_mainCamera )
		m_mainCamera = this;
}

cCamera::~cCamera()
{
	cInputManager::GetR().UnSubscribe( this );

	if ( m_mainCamera == this )
		m_mainCamera = nullptr;
}

void cCamera::Update( float _deltaTime, int _width, int _height )
{

	const glm::vec3 forward = { cos( glm::radians( m_rot.y ) ) * cos( glm::radians( m_rot.x ) ), sin( glm::radians( m_rot.x ) ), sin( glm::radians( m_rot.y ) ) * cos( glm::radians( m_rot.x ) ) };
	const glm::vec3 up        = glm::vec3( 0.0f, 1.0f, 0.0f );
	const glm::vec3 Right     = glm::normalize( glm::cross( up, forward ) );

	m_view = glm::lookAt( glm::vec3( m_pos ), glm::vec3( m_pos ) + forward, up );
	m_proj = glm::perspective( glm::radians( 45.0f ), ( float )_width / ( float )_height, 0.1f, 8192.0f );
}
