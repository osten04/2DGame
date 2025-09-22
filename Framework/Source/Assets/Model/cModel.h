#pragma once

#include "Assets/cAsset.h"
#include "cModelManager.h"

#include "glm/ext.hpp"

class cModel : public cAsset< cModelManager >
{
protected:
	friend cModelManager;
	unsigned int m_vao, m_vbo, m_vertexCount;
public:
	cModel( const char* _path );
	~cModel();

	glm::mat4x4 m_mat = glm::mat4x4( 1.0f );
};

