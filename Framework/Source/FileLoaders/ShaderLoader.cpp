#include "ShaderLoader.h"

#include "glad/glad.h"

#include <string>
#include <fstream>

unsigned int loadShader( const char* _path, unsigned int _type )
{
    std::ifstream ifs( _path );
    const char* content = std::string((std::istreambuf_iterator<char>(ifs)),
        (std::istreambuf_iterator<char>())).c_str();

    ifs.close();

    unsigned int Shader;
    Shader = glCreateShader( _type );

    glShaderSource( Shader, 1, &content, NULL );
    glCompileShader( Shader );

    return Shader;
}
