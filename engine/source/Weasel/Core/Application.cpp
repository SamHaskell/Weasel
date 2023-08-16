#include "Weasel/Core/Application.hpp"

#include "Weasel/Core/GameObject.hpp"
#include "Weasel/Core/Model.hpp"

#include "Weasel/Input/Input.hpp"

#include "Weasel/Components/MeshInstance.hpp"
#include "Weasel/Components/VirtualCamera.hpp"
#include "Weasel/Components/EditorCameraController.hpp"

#include "Weasel/Graphics/RenderTypes.hpp"
#include "Weasel/Graphics/Shader.hpp"
#include "Weasel/Graphics/Mesh.hpp"
#include "Weasel/Graphics/Textures.hpp"
#include "Weasel/Graphics/Buffers.hpp"
#include "Weasel/Graphics/Cameras.hpp"
#include "Weasel/Graphics/Lights.hpp"

namespace Weasel
{
    Application::Application() {
        WindowSpec spec = {};
        m_Window = Window::Create(spec);
        m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
        m_Window->SetClearColor(0.2, 0.2, 0.2, 1.0);
        Input::SetActiveWindow(m_Window);
        m_Renderer = Renderer::Create();
    }

    Application::~Application() {}

    bool Application::Run()
    {
        glCullFace(GL_BACK);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);

        f64 dt = 0.0;
        f64 elapsed = 0.0;
        auto now = std::chrono::high_resolution_clock::now();

        m_Running = true;
        while (m_Running)
        {            
            m_Window->Update(dt);
            
            ////////////////////////////////////////////////////////

            // GAME LOOP

            for (auto layer : m_AppStack.Layers) { layer->Update(dt); }
            for (auto layer : m_AppStack.Layers) { layer->LateUpdate(dt); }
            for (auto overlay : m_AppStack.Overlays) { overlay->Update(dt); }
            for (auto overlay : m_AppStack.Overlays) { overlay->LateUpdate(dt); }

            for (auto layer : m_AppStack.Layers) { layer->Render(m_Renderer); }
            for (auto overlay : m_AppStack.Overlays) { overlay->Render(m_Renderer); }

            // GUI RENDERING

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            for (auto layer : m_AppStack.Layers) { layer->ImGuiRender(); }
            for (auto overlay : m_AppStack.Overlays) { overlay->ImGuiRender(); }

            ImGui::Button("Hello!", {100, 100});
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            // TIMING

            auto next = std::chrono::high_resolution_clock::now();
            dt = std::chrono::duration<f64, std::chrono::seconds::period>(next - now).count();
            elapsed += dt;
            now = next;
        }
        return true;
    }

    bool Application::OnEvent(Event &e)
    {
        switch (e.Tag) {
            case EventTag::WindowCloseEvent:
                m_Running = false;
                break;
            case EventTag::WindowFramebufferSizeEvent:
                glViewport(0, 0, e.WindowFramebufferSizeEvent.Width, e.WindowFramebufferSizeEvent.Height);
                break;
            default:
                break;
        }

        for (auto overlay : m_AppStack.Overlays) { if (overlay->OnEvent(e)) return true; }
        for (auto layer : m_AppStack.Layers) { if (layer->OnEvent(e)) return true; }

        return true;
    }
}