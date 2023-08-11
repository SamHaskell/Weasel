#include "Weasel/Core/Application.hpp"

#include "glad/glad.h"
#include <iostream>

#include "Weasel/Graphics/RenderTypes.hpp"
#include "Weasel/Graphics/Shader.hpp"
#include "Weasel/Graphics/Model.hpp"
#include "Weasel/Graphics/Textures.hpp"
#include "Weasel/Graphics/Buffers.hpp"
#include "Weasel/Graphics/Cameras.hpp"
#include "Weasel/Graphics/Lights.hpp"

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
            {.Position = {+1.0f, -1.0f, -1.0f}, .Normal = {+1.0f, +0.0f, +0.0f}},
            {.Position = {+1.0f, +1.0f, -1.0f}, .Normal = {+1.0f, +0.0f, +0.0f}},
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

        std::vector<Vertex> quadVertices {
            {.Position = {-0.5f, -0.5f, +0.0f}},
            {.Position = {+0.5f, -0.5f, +0.0f}},
            {.Position = {+0.5f, +0.5f, +0.0f}},
            {.Position = {-0.5f, +0.5f, +0.0f}}  
        };

        std::vector<Index> quadIndices {
            0, 1, 2, 2, 3, 0  
        };

        // set up the model
        u32 VAO;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        u32 VBO;    
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(
            GL_ARRAY_BUFFER, 
            sizeof(Vertex) * static_cast<u32>(cubeVertices.size()), 
            cubeVertices.data(), 
            GL_STATIC_DRAW
        );

        u32 IBO;
        glGenBuffers(1, &IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            sizeof(Index) * static_cast<u32>(cubeIndices.size()),
            cubeIndices.data(),
            GL_STATIC_DRAW
        );

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoord));
        glEnableVertexAttribArray(3);

        u32 lightVAO;
        glGenVertexArrays(1, &lightVAO);
        glBindVertexArray(lightVAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
        glEnableVertexAttribArray(0);

        auto shaderRepository = ShaderRepository::Create();
        auto litShader = shaderRepository->Load(
            "lit", 
            "../../testbed/assets/builtin/shaders/default_lit.vert", 
            "../../testbed/assets/builtin/shaders/default_lit.frag"
        );
        auto lightShader = shaderRepository->Load(
            "light", 
            "../../testbed/assets/builtin/shaders/default_light.vert", 
            "../../testbed/assets/builtin/shaders/default_light.frag"
        );

        Camera mainCamera;
        glm::vec3 mainCameraPosition = glm::vec3(2.0f, 2.0f, 2.0f);
        mainCamera.SetPerspectiveProjection(60.0f, m_Window->GetAspectRatio(), 0.1f, 1000.0f);
        mainCamera.SetViewTarget(mainCameraPosition, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        DirectionalLight mainLight;
        glm::vec3 mainLightPosition = glm::vec3(-4.0f, 3.0f, -2.0f);
        mainLight.Color = glm::vec3(1.0f, 1.0f, 1.0f);

        glCullFace(GL_BACK);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);

        m_Running = true;
        while (m_Running)
        {            
            m_Window->Update();

            litShader->Bind();
            litShader->SetUniformMat4("u_ModelToWorldSpace", glm::mat4(1.0f));
            litShader->SetUniformMat4("u_WorldToClipSpace", mainCamera.ProjectionMatrix * mainCamera.ViewMatrix);
            litShader->SetUniformVec3("u_LightColor", mainLight.Color);
            litShader->SetUniformVec3("u_LightPosition", mainLightPosition);
            litShader->SetUniformVec3("u_CameraPosition", mainCameraPosition);

            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, static_cast<u32>(cubeIndices.size()), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);

            lightShader->Bind();
            lightShader->SetUniformMat4("u_ModelToWorldSpace", glm::scale(glm::translate(glm::mat4(1.0f), mainLightPosition), glm::vec3(0.2f, 0.2f, 0.2f)));
            lightShader->SetUniformMat4("u_WorldToClipSpace", mainCamera.ProjectionMatrix * mainCamera.ViewMatrix);
            lightShader->SetUniformVec3("u_ObjectColor", glm::vec3(1.0f, 1.0f, 1.0f));

            glBindVertexArray(lightVAO);
            glDrawElements(GL_TRIANGLES, static_cast<u32>(cubeIndices.size()), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();

            ImGui::NewFrame();
            ImGui::Button("Hello!", {100, 100});
            ImGui::Render();

            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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