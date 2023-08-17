#include "Weasel/Core/Application.hpp"
#include "Weasel/Core/Layer.hpp"
#include "Weasel/Input/Input.hpp"

namespace Weasel
{
    Application::Application(AppConfig config) {
        WindowConfig wConfig = {.Title = config.Name.c_str(), .Width = (i32)config.InitWidth, .Height = (i32)config.InitHeight};
        m_Window = Window::Create(wConfig);
        m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
        m_Window->SetClearColor(0.2, 0.2, 0.2, 1.0);
        Input::SetActiveWindow(m_Window);
        
        m_Renderer = Renderer::Create();

        m_AppState = {
            .Name = config.Name,
            .WindowWidth = config.InitWidth,
            .WindowHeight = config.InitHeight,
            .WindowFramebufferWidth = m_Window->GetFramebufferWidth(),
            .WindowFramebufferHeight = m_Window->GetFramebufferHeight()
        };
    }

    Application::~Application() {}

    bool Application::Run()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)m_Window->GetNativeHandle(), true);
        ImGui_ImplOpenGL3_Init("#version 410 core");

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

            for (auto layer : m_AppStack.Layers) { layer->RenderGUI(); }
            for (auto overlay : m_AppStack.Overlays) { overlay->RenderGUI(); }

            io.DisplaySize = ImVec2((i32)m_AppState.WindowWidth, (i32)m_AppState.WindowHeight);

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
                GLFWwindow* backup_context = (GLFWwindow*)m_Window->GetNativeHandle();
                ImGui::UpdatePlatformWindows();
                ImGui::RenderPlatformWindowsDefault();
                glfwMakeContextCurrent(backup_context);
            }

            // TIMING

            auto next = std::chrono::high_resolution_clock::now();
            dt = std::chrono::duration<f64, std::chrono::seconds::period>(next - now).count();
            elapsed += dt;
            now = next;
        }
        return true;

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
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