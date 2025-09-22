#include "GLFW/glfw3.h"

#include "Math/Vector.h"

class cModel;
class cSpriteSolid;

class cScene
{
public:
	cScene( GLFWwindow* _window );
	~cScene();

	void Update( double _deltatime, const math::sVector2i& _screenSize );

private:
	cModel*       m_model;
	cSpriteSolid* m_sprite;
};