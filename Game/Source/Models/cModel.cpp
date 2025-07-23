#include "cModel.h"

cMesh::cMesh( std::vector< Vertex > _vertices, std::vector< unsigned int > _indices, std::vector< Texture > _textures )
	: m_mat( 1.0f )
	, m_vba( 0 )
	, m_vbo( 0 )
	, m_ebo( 0 )
{
	
}

cMesh::~cMesh()
{
}