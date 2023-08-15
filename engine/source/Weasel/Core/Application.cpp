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
        editorCamera->Transform.SetLocalPosition(glm::vec3(6.0f, 0.0f, 6.0f));
        auto fwd = glm::normalize(glm::vec3(-1.0f, 0.0f, -1.0f));
        editorCamera->Transform.SetLocalRotation(glm::quatLookAt(fwd, glm::vec3(0.0f, 1.0f, 0.0f)));

        auto cubeMesh = Mesh::Create(cubeVertices, cubeIndices);
        auto cubeMaterial = Material::Create();
        
        auto cube = m_ActiveScene->InstantiateGameObject();
        auto cubeMeshInstance = cube->AddComponent<MeshInstance>();
        cubeMeshInstance->SetMesh(cubeMesh);
        cubeMeshInstance->SetMaterial(cubeMaterial);

        auto model = Model::Load("../../testbed/assets/user/models/backpack/backpack.obj");
        auto diffuse = Texture2D::Create("../../testbed/assets/user/models/backpack/diffuse.jpg");
        auto normal = Texture2D::Create("../../testbed/assets/user/models/backpack/normal.png");
        auto specular = Texture2D::Create("../../testbed/assets/user/models/backpack/specular.jpg");

        DirectionalLight dirLight {
            .Direction = glm::vec3(-1.0f, -1.0f, -1.0f),
            .Ambient = glm::vec3(0.05f, 0.05f, 0.05f),
            .Diffuse = glm::vec3(0.4f, 0.4f, 0.4f),
            .Specular = glm::vec3(0.5f, 0.5f, 0.5f)
        };

        PointLight pointLights[4];
        glm::vec3 lightPositions[4] = {
            {-4.0f, +2.0f, -4.0f},
            {+4.0f, +2.0f, -4.0f},
            {+4.0f, +2.0f, +4.0f},
            {-4.0f, +2.0f, +4.0f}
        };

        for (i32 i = 0; i < 4; i++) {
            pointLights[i] = {
                .Position = lightPositions[i],
                .Ambient = glm::vec3(0.05f, 0.05f, 0.05f),
                .Diffuse = glm::vec3(0.8f, 0.8f, 0.8f),
                .Specular = glm::vec3(1.0f, 1.0f, 1.0f),
                .Constant = 1.0f,
                .Linear = 0.09f,
                .Quadratic = 0.032f
            };
        }

        glCullFace(GL_BACK);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);

        m_Running = true;
        f64 dt = 0.0;
        f64 elapsed = 0.0;
        auto now = std::chrono::high_resolution_clock::now();

        m_ActiveScene->Awake();

        while (m_Running)
        {            
            m_Window->Update(dt);
            m_ActiveScene->Update(dt);
            m_ActiveScene->LateUpdate(dt);

            litShader->Bind();
            litShader->SetUniformMat4("u_WorldToClipSpace", m_ActiveScene->GetCameraViewProjectionMatrix());
            litShader->SetUniformVec3("u_CameraPosition", m_ActiveScene->GetCameraPosition());

            litShader->SetUniformVec3("u_DirLight.Direction", dirLight.Direction);
            litShader->SetUniformVec3("u_DirLight.Ambient", dirLight.Ambient);
            litShader->SetUniformVec3("u_DirLight.Diffuse", dirLight.Diffuse);
            litShader->SetUniformVec3("u_DirLight.Specular", dirLight.Specular);

            litShader->SetUniformVec3("u_PointLights[0].Position", pointLights[0].Position);
            litShader->SetUniformVec3("u_PointLights[0].Ambient", pointLights[0].Ambient);
            litShader->SetUniformVec3("u_PointLights[0].Diffuse", pointLights[0].Diffuse);
            litShader->SetUniformVec3("u_PointLights[0].Specular", pointLights[0].Specular);
            litShader->SetUniformFloat("u_PointLights[0].Constant", pointLights[0].Constant);
            litShader->SetUniformFloat("u_PointLights[0].Linear", pointLights[0].Linear);
            litShader->SetUniformFloat("u_PointLights[0].Quadratic", pointLights[0].Quadratic);

            litShader->SetUniformVec3("u_PointLights[1].Position", pointLights[1].Position);
            litShader->SetUniformVec3("u_PointLights[1].Ambient", pointLights[1].Ambient);
            litShader->SetUniformVec3("u_PointLights[1].Diffuse", pointLights[1].Diffuse);
            litShader->SetUniformVec3("u_PointLights[1].Specular", pointLights[1].Specular);
            litShader->SetUniformFloat("u_PointLights[1].Constant", pointLights[1].Constant);
            litShader->SetUniformFloat("u_PointLights[1].Linear", pointLights[1].Linear);
            litShader->SetUniformFloat("u_PointLights[1].Quadratic", pointLights[1].Quadratic);

            litShader->SetUniformVec3("u_PointLights[2].Position", pointLights[2].Position);
            litShader->SetUniformVec3("u_PointLights[2].Ambient", pointLights[2].Ambient);
            litShader->SetUniformVec3("u_PointLights[2].Diffuse", pointLights[2].Diffuse);
            litShader->SetUniformVec3("u_PointLights[2].Specular", pointLights[2].Specular);
            litShader->SetUniformFloat("u_PointLights[2].Constant", pointLights[2].Constant);
            litShader->SetUniformFloat("u_PointLights[2].Linear", pointLights[2].Linear);
            litShader->SetUniformFloat("u_PointLights[2].Quadratic", pointLights[2].Quadratic);

            litShader->SetUniformVec3("u_PointLights[3].Position", pointLights[3].Position);
            litShader->SetUniformVec3("u_PointLights[3].Ambient", pointLights[3].Ambient);
            litShader->SetUniformVec3("u_PointLights[3].Diffuse", pointLights[3].Diffuse);
            litShader->SetUniformVec3("u_PointLights[3].Specular", pointLights[3].Specular);
            litShader->SetUniformFloat("u_PointLights[3].Constant", pointLights[3].Constant);
            litShader->SetUniformFloat("u_PointLights[3].Linear", pointLights[3].Linear);
            litShader->SetUniformFloat("u_PointLights[3].Quadratic", pointLights[3].Quadratic);

            litShader->SetSamplerSlot("u_Material.DiffuseMap", 0);
            litShader->SetSamplerSlot("u_Material.NormalMap", 1);
            litShader->SetSamplerSlot("u_Material.SpecularMap", 2);

            diffuse->Bind(0);
            normal->Bind(1);
            specular->Bind(2);

            for (i32 i = 0; i < 5; i++) {
                cube->Transform.SetLocalPosition(glm::vec3(-10.0f + 5.0f * i, 0.0f, 0.0f));
                litShader->SetUniformMat4("u_ModelToWorldSpace", cube->Transform.WorldTransform());
                for (auto mesh : model->m_Meshes) {
                    m_Renderer->DrawMesh(mesh, cubeMaterial);
                }
            }

            lightShader->Bind();
            lightShader->SetUniformMat4("u_WorldToClipSpace", m_ActiveScene->GetCameraViewProjectionMatrix());
            lightShader->SetUniformVec3("u_ObjectColor", glm::vec3(1.0f, 1.0f, 1.0f));

            for (i32 i = 0; i < 4; i++) { 
                lightShader->SetUniformMat4("u_ModelToWorldSpace", glm::scale(glm::translate(glm::mat4(1.0f), pointLights[i].Position), glm::vec3(0.2f, 0.2f, 0.2f)));
                cubeMesh->Draw(); }

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
            case EventTag::WindowFramebufferSizeEvent:
                glViewport(0, 0, e.WindowFramebufferSizeEvent.Width, e.WindowFramebufferSizeEvent.Height);
                break;
            default:
                break;
        }
        m_ActiveScene->OnEvent(e);
        return true;
    }
}