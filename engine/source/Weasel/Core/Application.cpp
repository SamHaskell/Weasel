#include "Weasel/Core/Application.hpp"

#include "glad/glad.h"
#include <iostream>

namespace Weasel
{
    Application::Application() {}

    Application::~Application() {}

    bool Application::Run()
    {
        WindowSpec spec = {};
        m_Window = Window::Create(spec);
        m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

        m_Running = true;
        while (m_Running)
        {
            m_Window->Update();
        }
        return true;
    }

    bool Application::OnEvent(Event &e)
    {
        switch (e.Tag)
        {
        case EventTag::WindowCloseEvent:
            m_Running = false;
            break;
        default:
            break;
        }

        return true;
    }
}