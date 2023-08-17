#pragma once

#include "Weasel/Base/Base.hpp"
#include "Weasel/Events/Events.hpp"
#include "Weasel/Core/Window.hpp"
#include "Weasel/Core/AppStack.hpp"
#include "Weasel/Core/Scene.hpp"
#include "Weasel/Graphics/Renderer.hpp"

namespace Weasel {
    struct AppConfig {
        std::string Name;
        u32 InitWidth;
        u32 InitHeight;
    };

    struct AppState {
        std::string Name;
        u32 WindowWidth;
        u32 WindowHeight;
        u32 WindowFramebufferWidth;
        u32 WindowFramebufferHeight;
    };

    class Application {
    public:
        Application(AppConfig config);
        virtual ~Application();
        bool Run();
        bool OnEvent(Event &e);
    protected:
        AppStack m_AppStack;
        AppState m_AppState;
    private:
        bool m_Running;
        std::unique_ptr<Window> m_Window;
        std::unique_ptr<Renderer> m_Renderer;
    };

    Application *CreateApplication();
}