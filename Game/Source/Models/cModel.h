#include <string>

#include <glm/matrix.hpp>
#include <string>
#include <vector>
#include <glad/glad.h>

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture {
	unsigned int id;
	std::string type;
};

class cMesh
{
public:
	cMesh( std::vector< Vertex > _vertices, std::vector< unsigned int > _indices, std::vector< Texture > _textures );
	~cMesh();

	const glm::mat4x4& GetMat() { return m_mat; }

	void Draw( Shader& _shader );

	std::vector<Vertex>       vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture>      textures;

private:
	glm::mat4x4 m_mat;

	unsigned int m_vbo, m_vba, m_ebo;


};