#include "GameViewport.h"

#include "imgui.h"

#include "glad/glad.h"

#include "DllLayer/DllLoad.h"

void AlignForWidth(float width, float alignment = 0.5f)
{
    ImGuiStyle& style = ImGui::GetStyle();
    float avail = ImGui::GetContentRegionAvail().x;
    float off = (avail - width) * alignment;
    if (off > 0.0f)
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);
}

void GameViewport::mainLoop()
{

    if (ImGui::Begin( "Dummy", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar ) )
    {
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Menu"))
            {
                ImGui::MenuItem("Console", NULL );
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        ImVec2 buttonSize( 20, 20 );

        float width = ImGui::GetStyle().ItemSpacing.x;

        if ( m_GameRunning )
            width += buttonSize.x * 3;
        else
            width += buttonSize.x;
        AlignForWidth(width);

        auto& io = ImGui::GetIO();

        m_GameRunning;

        if (m_GameRunning)
            ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(0xff4d40bd));
        else
            ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(0xff7ee07e));
        
        if ( ImGui::Button("##Start", buttonSize) )
        {
            if (m_GameRunning)
            {
                UnloadGameDll();
                m_GameRunning = false;
            }
            else
            {

                InitGameDll();
                m_GameRunning = true;
            }
        }
        ImGui::PopStyleColor(1);

        if (m_GameRunning)
        {

            ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(0xffb2b2b2));
            ImGui::SameLine();
            if( ImGui::Button( "##Break", buttonSize) )
                printf( "Break\n" );


            ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(0xffca9146));
            ImGui::SameLine();
            if (ImGui::Button("##Restart", buttonSize))
            {
                UnloadGameDll();
                InitGameDll();
            }

            ImGui::PopStyleColor(2);
        }

        // 3. Show another simple window.
        if (m_GameRunning)
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
    }
    ImGui::End();
}
