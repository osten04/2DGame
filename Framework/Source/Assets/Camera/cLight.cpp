#include "cLight.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

cLight::cLight()
	: Super( false )
{
	float near_plane = 1.0f, far_plane = 512.0f;
	m_proj = glm::ortho( -100.0f, 100.0f, -100.0f, 010.0f, near_plane, far_plane );
	m_view = glm::lookAt( glm::vec3( -2.0f, 4.0f, -1.0f ), glm::vec3( 0.0f, 2.0f, 0.0f ), glm::vec3( 0.0f, 1.0f, 0.0f ) );
}

void cLight::Update( float _deltaTime, int _width, int _height )
{
}
