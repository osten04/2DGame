#include "glad/glad.h"

#include "Assets/cAssetRenderer.h"
#include "Sprite/cSprite.h"

class cSpriteManager : public cAssetRenderer< cSprite >
{
private:
	GLuint m_shaderProgram;
	GLuint m_whiteTexture;
	GLint  m_colorUniformLocation;


public:
	cSpriteManager();

protected:
	void draw( cSprite* _sprite ) override;
	void setTexture(void);
};