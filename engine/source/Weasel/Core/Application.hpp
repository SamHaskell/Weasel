#pragma once

#include "Weasel/Base/Base.hpp"
#include "Weasel/Events/Events.hpp"
#include "Weasel/Core/Window.hpp"

namespace Weasel
{
    class Application
    {
    public:
        Application();
        virtual ~Application();
        bool Run();
        bool OnEvent(Event &e);

    private:
        bool m_Running;
        Window* m_Window;
    };

    Application *CreateApplication();
}