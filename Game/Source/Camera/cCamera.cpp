#include "cCamera.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtx/transform.hpp>

cCamera* cCamera::m_mainCamera;

cCamera::cCamera( GLFWwindow* _glfwWindow )
{
	glfwSetCursorPosCallback(_glfwWindow, []( GLFWwindow* _window, double _xpos, double _ypos ) { cCamera::getMainCamera()->MouseCallback( _window, _xpos, _ypos ); } );
}

cCamera::~cCamera()
{
}

void cCamera::Update( float _deltaTime, int _width, int _height )
{
	glm::mat4 view = glm::translate( glm::mat4( 1.0f ), glm::vec3( 0.0f, 0.0f, -3.0f ) );
	glm::mat4 proj = glm::perspective( glm::radians( 45.0f ), ( float )_width / ( float )_height, 0.1f, 100.0f );
}

void cCamera::MouseCallback( GLFWwindow* _window, double _xpos, double _ypos )
{
	glm::dvec2 newPos = glm::dvec2( _xpos, _ypos );
	m_rot += ( newPos - m_lastFrameMousePos ) * m_sens;
	m_lastFrameMousePos = newPos;
}
