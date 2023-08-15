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
    Application::Application() {}

    Application::~Application() {}

    bool Application::Run()
    {
        WindowSpec spec = {};
        m_Window = Window::Create(spec);
        m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
        m_Window->SetClearColor(0.2, 0.2, 0.2, 1.0);
        Input::SetActiveWindow(m_Window);

        m_Renderer = Renderer::Create();

        m_ActiveScene = Scene::Create();
        m_ActiveScene->AspectRatio = m_Window->GetAspectRatio();

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

        auto editorCamera = m_ActiveScene->InstantiateGameObject();
        auto editorVCamera = editorCamera->AddComponent<VirtualCamera>();
        auto editorCameraController = editorCamera->AddComponent<EditorCameraController>();

        editorVCamera->MakeActive();
        editorCamera->Transform.SetLocalPosition(glm::vec3(6.0f, 6.0f, 6.0f));
        auto fwd = glm::normalize(glm::vec3(-1.0f, -1.0f, -1.0f));
        editorCamera->Transform.SetLocalRotation(glm::quatLookAt(fwd, glm::vec3(0.0f, 1.0f, 0.0f)));

        auto cubeMesh = Mesh::Create(cubeVertices, cubeIndices);
        auto cubeMaterial = Material::Create();
        
        auto cube = m_ActiveScene->InstantiateGameObject();
        auto cubeMeshInstance = cube->AddComponent<MeshInstance>();
        cubeMeshInstance->SetMesh(cubeMesh);
        cubeMeshInstance->SetMaterial(cubeMaterial);

        auto model = Model::Load("../../testbed/assets/user/models/backpack/backpack.obj");

        DirectionalLight mainLight;
        glm::vec3 mainLightPosition = glm::vec3(-2.0f, 3.0f, 3.0f);
        mainLight.Color = glm::vec3(1.0f, 1.0f, 1.0f);

        glCullFace(GL_BACK);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);

        m_Running = true;
        f64 dt = 0.0;
        f64 elapsed = 0.0;
        auto now = std::chrono::high_resolution_clock::now();
        while (m_Running)
        {            
            m_Window->Update(dt);
            m_ActiveScene->Update(dt);

            litShader->Bind();
            litShader->SetUniformMat4("u_ModelToWorldSpace", glm::mat4(1.0f));
            litShader->SetUniformMat4("u_WorldToClipSpace", m_ActiveScene->GetCameraViewProjectionMatrix());
            litShader->SetUniformVec3("u_LightColor", mainLight.Color);
            litShader->SetUniformVec3("u_LightPosition", mainLightPosition);
            litShader->SetUniformVec3("u_CameraPosition", m_ActiveScene->GetCameraPosition());

            // cubeMesh->Draw();
            for (auto mesh : model->m_Meshes) {
                m_Renderer->DrawMesh(mesh, cubeMaterial);
            }

            lightShader->Bind();
            lightShader->SetUniformMat4("u_ModelToWorldSpace", glm::scale(glm::translate(glm::mat4(1.0f), mainLightPosition), glm::vec3(0.2f, 0.2f, 0.2f)));
            lightShader->SetUniformMat4("u_WorldToClipSpace", m_ActiveScene->GetCameraViewProjectionMatrix());
            lightShader->SetUniformVec3("u_ObjectColor", glm::vec3(1.0f, 1.0f, 1.0f));

            cubeMesh->Draw();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();

            ImGui::NewFrame();
            ImGui::Button("Hello!", {100, 100});
            ImGui::Render();

            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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
            default:
                break;
        }
        m_ActiveScene->OnEvent(e);
        return true;
    }
}