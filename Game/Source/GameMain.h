#include "glad/glad.h"

extern "C" int    __declspec( dllexport ) init( void );
extern "C" int    __declspec( dllexport ) close();
extern "C" GLenum __declspec( dllexport ) draw( int _width, int _height );