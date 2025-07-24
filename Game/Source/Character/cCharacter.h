
#include "GLFW/glfw3.h"

#include "input/cInput.hpp"
#include "Sprite/cSprite.h"

struct sKeyBinds
{
	int left, right, jump;
};

class cCharacter
{
public:
	cCharacter();
	~cCharacter();

	void Update( double _deltaTime );
	
	void Input( const sInput& _input );

private:
	sKeyBinds m_binds;

	enum eInputsMask : int
	{
		none  = 0x00,
		left  = 0x01,
		right = 0x02,
		jump  = 0x04
	};

	int m_input = none;

	eInputsMask GetInputMask( int _input );

	cSpriteSolid* m_sprite;

	math::sVector2f m_vel = { 0.0f, 0.0f };

	bool m_gounded = false;
};