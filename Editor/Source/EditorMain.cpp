#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <stdio.h>

#include "EditorImGUI/GameViewport.h"

#include "Windows.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include <dwmapi.h>
void tittleBar( GLFWwindow* _glfwWindow )
{
    HWND window = glfwGetWin32Window( _glfwWindow );

    BOOL USE_DARK_MODE = true;
    DwmSetWindowAttribute( window, DWMWINDOWATTRIBUTE::DWMWA_USE_IMMERSIVE_DARK_MODE, &USE_DARK_MODE, sizeof(USE_DARK_MODE) );

    ShowWindow(window, SW_MINIMIZE);
    ShowWindow(window, SW_RESTORE);

    RECT rcClient;
    GetWindowRect( window, &rcClient);

    // Inform the application of the frame change.
    SetWindowPos( window,
        NULL,
        rcClient.left, rcClient.top,
        rcClient.right - rcClient.left, rcClient.bottom - rcClient.top,
        SWP_FRAMECHANGED);
}

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

// Main code
__declspec(dllexport) int EditorMain()
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    const char* glsl_version = "#version 460";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    //glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    //glfwWindowHint(GLFW_MOUSE_PASSTHROUGH, GLFW_TRUE);

    //glfwWindowHint(GLFW_VISIBLE, GL_FALSE);


    // Create window with graphics context
    GLFWwindow* window;
    /*{
        int monitorCount;
        GLFWmonitor** monitors = glfwGetMonitors( &monitorCount );

        int xmin, ymin, xmax, ymax;
        glfwGetMonitorWorkarea( glfwGetPrimaryMonitor(), &xmin, &ymin, &xmax, &ymax );
        xmax += xmin;
        ymax += ymin;

        for (size_t i = 0; i < monitorCount; i++)
        {
            int x, y, width, height;
            glfwGetMonitorWorkarea( monitors[ i ], &x, &y, &width, &height);

            int monitorXmax = x + width;
            int monitorYmax = y + height;

            if ( x < xmin ) xmin = x;
            if ( y < ymin ) ymin = y;
            if ( monitorXmax > xmax ) xmax = monitorXmax;
            if ( monitorYmax > ymax ) ymax = monitorYmax;
        }
        window = glfwCreateWindow( xmax - xmin, ymax - ymin, "Dummy", nullptr, nullptr);
        glfwSetWindowPos(window, xmin, ymin);
    }*/
    window = glfwCreateWindow(900, 600, "", nullptr, nullptr);

    if (window == nullptr)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0); // Enable vsync

    tittleBar( window );
    glfwSetInputMode( window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE );

    unsigned char byte[ 4 ] = { 0,0,0,0 };
    GLFWimage image = GLFWimage( 1, 1, byte );

    //glfwSetWindowIcon( window, 1, &image );

    gladLoadGL();


    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);

    ImGui_ImplOpenGL3_Init(glsl_version);

    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);

    GameViewport::init();

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0)
        {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        float padding = 5;
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(padding, padding));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.0f);

        
        ImGui::DockSpaceOverViewport();
        
        GameViewport::GetR().mainLoop( window );

        ImGui::PopStyleVar(3);

        // Rendering
        ImGui::Render();

        // Update and Render additional Platform Windows
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            // TODO for OpenGL: restore current GL context.
        }

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}