#include "ShaderLoader.h"

#include "glad/glad.h"

#include <string>
#include <fstream>

#include <filesystem>
#include <iostream>

unsigned int loadShader( const char* _path, unsigned int _type )
{
    // Open the file using ifstream
    std::ifstream file(_path);

    // confirm file opening
    if (!file.is_open()) {
        // print error message and return
        std::cerr << "Failed to open file: " << _path << std::endl;

        return 1;
    }

    // Read the file line by line into a string
    std::string str;

    for (std::string line; getline(file, line); ) {
        str += line;
    }

    const char* source = str.c_str();


    // Close the file
    file.close();

    unsigned int Shader;
    Shader = glCreateShader( _type );

    glShaderSource( Shader, 1, &source, NULL);
    glCompileShader( Shader );

    return Shader;
}
