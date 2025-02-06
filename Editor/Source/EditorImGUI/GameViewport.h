#include "Singleton.hpp"

class GameViewport : public Singleton< GameViewport >
{
private:
	bool show_another_window;

public:
	void mainLoop();
};