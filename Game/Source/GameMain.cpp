#include <iostream>

#include "glad/glad.h"
#include "GameMain.h"

const GLchar* vertexShaderSource = "#version 460 core\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\0";
const GLchar* fragmentShaderSource = "#version 460 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";


GLuint shaderProgram = 0;

GLuint VBO, VAO;

GLenum fbo, textureColorbuffer;

#include "Assets/cAssetManager.h"
#include "Sprite/cSprite.h"
#include "Scene/cScene.h"


GLFWwindow* window;

void GLAPIENTRY
MessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
}

cScene* CurrentScene = nullptr;

int initBuffers( GLFWwindow* _window )
{
	glfwInit();

	gladLoadGL();

	// During init, enable debug output
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);

	window = _window;

	// Build and compile our shader program
	// Vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// Check for compile time errors
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// Check for compile time errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Link shaders
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// Check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Set up vertex data (and buffer(s)) and attribute pointers
	// We add a new set of vertices to form a second triangle (a total of 6 vertices); the vertex attribute configuration remains the same (still one 3-float position vector per vertex)
	GLfloat vertices[] = {
		// First triangle
		-0.9f, -0.5f, 0.0f,  // Left 
		-0.0f, -0.5f, 0.0f,  // Right
		-0.45f, 0.5f, 0.0f,  // Top 
		// Second triangle
		 0.0f, -0.5f, 0.0f,  // Left
		 0.9f, -0.5f, 0.0f,  // Right
		 0.45f, 0.5f, 0.0f,  // Top 

		 -0.45f, 0.5f, 0.0f,
		 -0.0f, -0.5f, 0.0f,
		  0.45f, 0.5f, 0.0f
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0);

	glGenFramebuffers(1, &fbo);

	glGenTextures(1, &textureColorbuffer);

	cAssetManager::init();
	cSpriteManager::init();

	CurrentScene = new cScene( window );

	return 0;
}

GLenum DrawGL( int _width, int _height )
{
	glViewport(0, 0, _width, _height);

	if( fbo )

	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	// generate texture
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	// attach it to currently bound framebuffer object
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

	glClear(GL_COLOR_BUFFER_BIT);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

	double deltaTime = glfwGetTime();

	CurrentScene->Update( deltaTime, { _width, _height } );

	cAssetManager::GetR().draw( math::sVector2i{ _width, _height } );

	glBindFramebuffer( GL_FRAMEBUFFER, 0 );

	glfwSetTime( 0.0 );

	return textureColorbuffer;
}

extern "C"
{
	int __declspec( dllexport ) init( GLFWwindow* _window )
	{
		return initBuffers( _window );
	}

	int __declspec(dllexport) close(void)
	{
		glDeleteTextures    ( 1, &textureColorbuffer );
		glDeleteFramebuffers( 1, &fbo );
		glDeleteBuffers     ( 1, &VBO );
		glDeleteVertexArrays( 1, &VAO );
		glDeleteProgram     ( shaderProgram );

		delete CurrentScene;

		cSpriteManager::destroy();
		cAssetManager::destroy();

		return 0;
	}

	GLenum __declspec( dllexport ) draw( int _width, int _height )
	{
		return DrawGL( _width, _height );
	}
}
