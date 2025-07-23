#include "Singleton.hpp"

#include "GLFW/glfw3.h"

class GameViewport : public Singleton< GameViewport >
{
private:
	bool m_GameRunning = false;

public:
	void mainLoop( GLFWwindow* _window );
};