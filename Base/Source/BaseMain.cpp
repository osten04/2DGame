
#ifdef EDITOR
#include <windows.h> 
#include <iostream> 
#include <DbgHelp.h> 

#include "EditorMain.h"
void printStackTrace() {
    void* backtrace[100];
    unsigned short frames;
    SYMBOL_INFO* symbol;
    HANDLE process = GetCurrentProcess();

    SymInitialize(process, NULL, TRUE);
    frames = CaptureStackBackTrace(0, 100, backtrace, NULL);
    symbol = (SYMBOL_INFO*)malloc(sizeof(SYMBOL_INFO) + 256 * sizeof(char));
    symbol->MaxNameLen = 255;
    symbol->SizeOfStruct = sizeof(SYMBOL_INFO);

    int size = frames;
    for (int i = size - 1; i >= 0; i--)
    {
        SymFromAddr(process, (DWORD64)(backtrace[i]), 0, symbol);
        std::cout << symbol->Name << " - " << symbol->Address << std::endl;
    }

    free(symbol);
}

LONG WINAPI ExceptionHandler(EXCEPTION_POINTERS* pExceptionInfo) {
    std::cerr << "Unhandled exception caught!" << std::endl;
    printStackTrace();
    return EXCEPTION_EXECUTE_HANDLER;
}

int main()
{
    SetUnhandledExceptionFilter(ExceptionHandler);

    return EditorMain();
}
#else // EDITOR

#include <stdio.h>

#include "GameMain.h"
#include "GLFW/glfw3.h"

float vertices[] = {
    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
     1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
     1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
};

const char* vertexShaderSource = 
"#version 460 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec2 aTexCoord;\n"
"out vec2 TexCoord;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"   TexCoord = aTexCoord;\n"
"}\0";

const char* fragmentShaderSource =
"#version 460 core\n"
"out vec4 FragColor;\n"
"in vec2 TexCoord;\n"
"uniform sampler2D ourTexture;\n"
"void main()\n"
"{\n"
"    FragColor = texture(ourTexture, TexCoord);\n"
"}\n";

void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s (%d)\n", description, error);
}

int main()
{
    glfwSetErrorCallback(error_callback);

    // initialize all the internal state of GLFW
    if (!glfwInit()) {
        return -1;
    }

    // create the window
    int resx = 640, resy = 480;
    GLFWwindow* window = glfwCreateWindow(resx, resy, "GLFW: Creating a window.", NULL, NULL);

    // check if the opening of the window failed whatever reason and clean up
    if (!window) {
        glfwTerminate();
        return -2;
    }

    // in principle we can have multiple windows, 
    // so we set the newly created on as "current"
    glfwMakeContextCurrent(window);

    // Enable v-sync for now, if possible
    glfwSwapInterval(0);

    gladLoadGL();

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);


    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader( vertexShader );
    glDeleteShader( fragmentShader );

    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    // ..:: Initialization code (done once (unless your object frequently changes)) :: ..
    // 1. bind Vertex Array Object
    glBindVertexArray(VAO);
    // 2. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. then set our vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    init( window );

    // main loop
    while (!glfwWindowShouldClose(window)) {
        // listen for events (keyboard, mouse, etc.). ignored for now, but useful later
        glfwPollEvents();

        // make it close on pressing escape
        if (glfwGetKey(window, GLFW_KEY_ESCAPE))
            glfwSetWindowShouldClose(window, GLFW_TRUE);

        GLenum tex = draw(resx, resy);
        
        // 2. use our shader program when we want to render an object
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glBindTexture( GL_TEXTURE_2D, tex );

        glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );

        // swap buffers (replace the old image with a new one)
        // this won't have any visible effect until we add actual drawing
        glfwSwapBuffers(window);
    }

    close();

    // clean up
    glfwTerminate();

    return 0;
}

#endif 