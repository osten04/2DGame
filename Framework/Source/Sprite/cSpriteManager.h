#include "glad/glad.h"

#include "Assets/cAssetRenderer.h"
#include "Sprite/cSprite.h"

class cSpriteManager : public cAssetRenderer< cSpriteSolid >
{
private:
	GLuint m_shaderProgram;
	GLint  m_colorUniformLocation;


public:
	cSpriteManager();

protected:
	void draw( cSpriteSolid* _sprite ) override;
};