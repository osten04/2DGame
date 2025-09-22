#include "cModel.h"

#include "vector"

struct sVertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

int count_lines( const char* path )
{
	FILE* file = fopen(path, "r");
	if (file == NULL) {
		printf("Impossible to open the file !\n");
		return false;
	}

	char buf[128];
	int counter = 0;
	for (;;)
	{
		size_t res = fread(buf, 1, 128, file);
		if (ferror(file))
			return -1;

		int i;
		for (i = 0; i < res; i++)
			if (buf[i] == '\n')
				counter++;

		if (feof(file))
			break;
	}

	fclose( file );
	return counter;
}

bool LoadOBJ( const char* path, std::vector < sVertex >& out_vertices )
{
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;

	int total_lines = count_lines( path );
	temp_vertices.reserve( total_lines );
	temp_uvs.reserve( total_lines );
	temp_normals.reserve( total_lines );

	FILE* file = fopen(path, "r");
	if (file == NULL) {
		printf("Impossible to open the file !\n");
		return false;
	}


	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader
		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return false;
			}
			vertexIndices.push_back( vertexIndex[0] );
			vertexIndices.push_back( vertexIndex[1] );
			vertexIndices.push_back( vertexIndex[2] );
			uvIndices.push_back( uvIndex[0] );
			uvIndices.push_back( uvIndex[1] );
			uvIndices.push_back( uvIndex[2] );
			normalIndices.push_back( normalIndex[0] );
			normalIndices.push_back( normalIndex[1] );
			normalIndices.push_back( normalIndex[2] );
		}
	}
	fclose( file );

	out_vertices.reserve( vertexIndices.size() );

	for ( unsigned int i = 0; i < vertexIndices.size(); i++ ) {
		unsigned int vertexIndex = vertexIndices[ i ] - 1;
		unsigned int normalIndex = normalIndices[ i ] - 1;
		unsigned int uvIndex     = uvIndices    [ i ] - 1;

		const sVertex vert =
		{
			.Position  = temp_vertices[ vertexIndex ],
			.Normal    = temp_normals [ normalIndex ],
			.TexCoords = temp_uvs     [ uvIndex     ]
		};

		out_vertices.push_back( vert );
	}

	return true;
}

#include "glad/glad.h"

cModel::cModel( const char* _path )
{
	// Read our .obj file
	std::vector< sVertex > vertices;
	bool res = LoadOBJ( _path, vertices );

	m_vertexCount = vertices.size();

	glGenVertexArrays( 1, &m_vao );
	glGenBuffers( 1, &m_vbo );

	glBindVertexArray( m_vao );
	glBindBuffer( GL_ARRAY_BUFFER, m_vbo );

	glBufferData( GL_ARRAY_BUFFER, vertices.size() * sizeof( sVertex ), vertices.data(), GL_STATIC_DRAW );

	// vertex positions
	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( sVertex ), ( void* ) 0 );
	// vertex normals
	glEnableVertexAttribArray( 1 );
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( sVertex ), ( void* ) offsetof( sVertex, Normal ) );
	// vertex texture coords
	glEnableVertexAttribArray( 2 );
	glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, sizeof( sVertex ), ( void* ) offsetof( sVertex, TexCoords ) );

	glBindVertexArray( 0 );
}

cModel::~cModel()
{
	glDeleteBuffers( 1, &m_vbo );
	glDeleteVertexArrays( 1, &m_vao );
}
