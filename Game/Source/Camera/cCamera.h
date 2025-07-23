#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"

#include "GLFW/glfw3.h"

class cCamera
{
public:
	cCamera( GLFWwindow* _glfwWindow );
	~cCamera();

	template< class... args >
	static void Init( args... ARGS ) { m_mainCamera = new cCamera( ARGS... ); }
	static void Deinit() { delete m_mainCamera; m_mainCamera = nullptr; }

	void Update( float _deltaTime, int _width, int _height );

	static cCamera* getMainCamera() { return m_mainCamera; };

	const glm::mat4x4& getMatrix() { return m_mat; }

	void MouseCallback( GLFWwindow* _window, double _xpos, double _Sypos );

private:

	static cCamera* m_mainCamera;

	glm::mat4  m_view = glm::mat4( 1.0f );
	glm::mat4  m_proj = glm::mat4( 1.0f );
	glm::dvec3 m_pos  = glm::vec3();
	glm::dvec2 m_rot  = glm::vec2();

	glm::dvec2 m_lastFrameMousePos = glm::vec2();

	double m_sens = 0.1;
};