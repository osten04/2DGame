#include "cAssetRenderer.h"

#include "glad/glad.h"
#include "FileLoaders/ShaderLoader.h"

#include <string>

unsigned int iAssetRenderer::CompileShader( const char* _shader )
{
    if( !_shader )
        return 0;

    unsigned int shader = glCreateProgram();
    
    std::string str = _shader;

    unsigned int vertexShader   = loadShader( ( str + "_vert.glsl" ).c_str(), GL_VERTEX_SHADER );
    unsigned int fragmentShader = loadShader( ( str + "_frag.glsl" ).c_str(), GL_FRAGMENT_SHADER );
    glAttachShader( shader, vertexShader );
    glAttachShader( shader, fragmentShader );
    glLinkProgram( shader );

    GLint success;
    GLchar infoLog[ 512 ];
    glGetProgramiv( shader, GL_LINK_STATUS, &success );
    if ( !success ) {
        glGetProgramInfoLog( shader, 512, NULL, infoLog );
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << '\n';
    }

    glDeleteShader( vertexShader );
    glDeleteShader( fragmentShader );

    return ( shader );
}

iAssetRenderer::iAssetRenderer( const char* _shader, const char* _shadowShader )
    : m_shaderProgram      ( CompileShader( _shader       ) )
    , m_shadowShaderProgram( CompileShader( _shadowShader ) )
{
    
}

iAssetRenderer::~iAssetRenderer()
{
    glDeleteProgram( m_shaderProgram );
}
