#include "glad/glad.h"

#include "Assets/cAssetRenderer.h"
#include "Sprite/cSprite.h"

class cSpriteManager : public cAssetRenderer< cSpriteSolid >
{
private:
	GLuint m_shaderProgram;
	GLint  m_colorUniformLocation;
	GLint  m_posUniformLocation;

public:
	cSpriteManager();

	void draw( cSpriteSolid* _asset );
};

