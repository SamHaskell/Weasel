#include "Weasel/Core/Application.hpp"

#include "glad/glad.h"
#include <iostream>

#include "Weasel/Graphics/RenderTypes.hpp"
#include "Weasel/Graphics/Shader.hpp"
#include "Weasel/Graphics/Model.hpp"
#include "Weasel/Graphics/Textures.hpp"
#include "Weasel/Graphics/Buffers.hpp"

namespace Weasel
{
    Application::Application() {}

    Application::~Application() {}

    bool Application::Run()
    {
        WindowSpec spec = {};
        m_Window = Window::Create(spec);
        m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
        m_Window->SetClearColor(0.2, 0.2, 0.2, 1.0);

        m_Renderer = Renderer::Create();

        // Manually stand up resources here while we develop the renderer ...

        std::vector<Vertex> cubeVertices {
            {.Position = {-1.0f, -1.0f, +1.0f}, .Normal = {+0.0f, +0.0f, +1.0f}}, //FRONT
            {.Position = {+1.0f, -1.0f, +1.0f}, .Normal = {+0.0f, +0.0f, +1.0f}},
            {.Position = {+1.0f, +1.0f, +1.0f}, .Normal = {+0.0f, +0.0f, +1.0f}},
            {.Position = {-1.0f, +1.0f, +1.0f}, .Normal = {+0.0f, +0.0f, +1.0f}},

            {.Position = {+1.0f, -1.0f, -1.0f}, .Normal = {+0.0f, +0.0f, -1.0f}}, //BACK
            {.Position = {-1.0f, -1.0f, -1.0f}, .Normal = {+0.0f, +0.0f, -1.0f}},
            {.Position = {-1.0f, +1.0f, -1.0f}, .Normal = {+0.0f, +0.0f, -1.0f}},
            {.Position = {+1.0f, +1.0f, -1.0f}, .Normal = {+0.0f, +0.0f, -1.0f}},

            {.Position = {-1.0f, +1.0f, +1.0f}, .Normal = {+0.0f, +1.0f, +0.0f}}, //TOP
            {.Position = {+1.0f, +1.0f, +1.0f}, .Normal = {+0.0f, +1.0f, +0.0f}},
            {.Position = {+1.0f, +1.0f, -1.0f}, .Normal = {+0.0f, +1.0f, +0.0f}},
            {.Position = {-1.0f, +1.0f, -1.0f}, .Normal = {+0.0f, +1.0f, +0.0f}},

            {.Position = {-1.0f, -1.0f, -1.0f}, .Normal = {+0.0f, -1.0f, +0.0f}}, //BOTTOM
            {.Position = {+1.0f, -1.0f, -1.0f}, .Normal = {+0.0f, -1.0f, +0.0f}},
            {.Position = {+1.0f, -1.0f, +1.0f}, .Normal = {+0.0f, -1.0f, +0.0f}},
            {.Position = {-1.0f, -1.0f, +1.0f}, .Normal = {+0.0f, -1.0f, +0.0f}},

            {.Position = {-1.0f, -1.0f, -1.0f}, .Normal = {-1.0f, +0.0f, +0.0f}}, //LEFT
            {.Position = {-1.0f, -1.0f, +1.0f}, .Normal = {-1.0f, +0.0f, +0.0f}},
            {.Position = {-1.0f, +1.0f, +1.0f}, .Normal = {-1.0f, +0.0f, +0.0f}},
            {.Position = {-1.0f, +1.0f, -1.0f}, .Normal = {-1.0f, +0.0f, +0.0f}},

            {.Position = {+1.0f, -1.0f, +1.0f}, .Normal = {+1.0f, +0.0f, +0.0f}}, //RIGHT
            {.Position = {-1.0f, -1.0f, -1.0f}, .Normal = {+1.0f, +0.0f, +0.0f}},
            {.Position = {-1.0f, +1.0f, -1.0f}, .Normal = {+1.0f, +0.0f, +0.0f}},
            {.Position = {+1.0f, +1.0f, +1.0f}, .Normal = {+1.0f, +0.0f, +0.0f}},
        };

        std::vector<Index> cubeIndices {
             0,  1,  2,  2,  3,  0, //FRONT
             4,  5,  6,  6,  7,  4, //BACK
             8,  9, 10, 10, 11,  8, //TOP
            12, 13, 14, 14, 15, 12, //BOTTOM
            16, 17, 18, 18, 19, 16, //LEFT
            20, 21, 22, 22, 23, 20, //RIGHT
        };

        auto shaderRepository = ShaderRepository::Create();
        auto unlitShader = shaderRepository->Load("unlit", "../../testbed/assets/builtin/shaders/unlit.vert", "../../testbed/assets/builtin/shaders/unlit.frag");

        m_Running = true;
        while (m_Running)
        {
            m_Window->Update();

            // unlitShader->Bind();

            // Manually do rendering here while we develop the renderer ...
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