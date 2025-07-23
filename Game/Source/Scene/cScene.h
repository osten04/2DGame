#include "GLFW/glfw3.h"

#include "Math/Vector.h"

class cSpriteSolid;

class cScene
{
public:
	cScene( GLFWwindow* _window );
	~cScene();

	void Update( double _deltatime, const math::sVector2i& _screenSize );

private:
	double m_time = 0.0;

	cSpriteSolid* m_sprite;
};