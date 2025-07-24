#include "GLFW/glfw3.h"

#include "Math/Vector.h"

class cSpriteSolid;
class cCharacter;

class cScene
{
public:
	cScene( GLFWwindow* _window );
	~cScene();

	void Update( double _deltatime, const math::sVector2i& _screenSize );

private:
	cCharacter* m_character;
};