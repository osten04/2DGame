#include "Singleton.hpp"

class GameViewport : public Singleton< GameViewport >
{
private:
	bool m_GameRunning;

public:
	void mainLoop();
};