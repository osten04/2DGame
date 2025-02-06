#include "GameViewport.h"

#include "imgui.h"

#include "glad/glad.h"

#include "DllLayer/DllLoad.h"

bool GameViewport::show_another_window;

void GameViewport::mainLoop()
{
    ImGui::Begin("Hello, world!");
    if (ImGui::Checkbox("Another Window", &show_another_window))
    {
        if (show_another_window)
        {
            InitGameDll();
        }
        else
        {
            unload();
        }
    }
    ImGui::End();


    // 3. Show another simple window.
    if (show_another_window)
    {
        ImGui::Begin("GameWindow");
        {
            // Using a Child allow to fill all the space of the window.
            // It also alows customization
            ImGui::BeginChild("GameRender");
            // Get the size of the child (i.e. the whole draw size of the windows).
            ImVec2 wsize = ImGui::GetWindowSize();

            GLenum texid = DrawGameDll(wsize.x, wsize.y);
            // Because I use the texture from OpenGL, I need to invert the V from the UV.
            ImGui::Image((ImTextureID)texid, wsize, ImVec2(0, 1), ImVec2(1, 0));
            //glDeleteTextures(1, &texid);
            ImGui::EndChild();
        }
        ImGui::End();
    }
}
