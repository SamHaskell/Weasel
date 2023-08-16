#pragma once

#include "Weasel/Base/Base.hpp"
#include "Weasel/Events/Events.hpp"
#include "Weasel/Core/Window.hpp"
#include "Weasel/Core/AppStack.hpp"
#include "Weasel/Core/Scene.hpp"
#include "Weasel/Graphics/Renderer.hpp"

namespace Weasel
{
    class Application
    {
    public:
        Application();
        virtual ~Application();
        bool Run();
        bool OnEvent(Event &e);
    protected:
        AppStack m_AppStack;
    private:
        bool m_Running;
        std::unique_ptr<Window> m_Window;
        std::unique_ptr<Renderer> m_Renderer;
    };

    Application *CreateApplication();
}