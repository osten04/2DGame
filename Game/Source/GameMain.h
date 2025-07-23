#include "glad/glad.h"

#include "GLFW/glfw3.h"

extern "C" int    __declspec( dllexport ) init( GLFWwindow* _window );
extern "C" int    __declspec( dllexport ) close();
extern "C" GLenum __declspec( dllexport ) draw( int _width, int _height );