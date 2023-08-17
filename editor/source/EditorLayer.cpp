#include "EditorLayer.hpp"

namespace Weasel {
    EditorLayer::EditorLayer(AppState state) : Layer(state) {
        m_Viewport = { 0, 1280, 0, 720 };
        m_ScreenExtents = {0, (f32)state.WindowFramebufferWidth, 0, (f32)state.WindowFramebufferHeight};
        m_FramebufferSpec = { .Width = 1280, .Height = 720 };
        m_Framebuffer = Framebuffer::Create(m_FramebufferSpec);
        m_FramebufferInvalid = false;
        m_ActiveScene = Scene::Create();
        m_ActiveScene->SetViewport(m_Viewport);

        m_ShaderRepository = ShaderRepository::Create();
        m_ShaderRepository->Load(
            "lit", 
            "../../testbed/assets/builtin/shaders/default_lit.vert", 
            "../../testbed/assets/builtin/shaders/default_lit.frag"
        );
        m_ShaderRepository->Load(
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

        m_BackpackModel = Model::Load("../../testbed/assets/user/models/backpack/backpack.obj");
        m_Diffuse = Texture2D::Create("../../testbed/assets/user/models/backpack/diffuse.jpg");
        m_Normal = Texture2D::Create("../../testbed/assets/user/models/backpack/normal.png");
        m_Specular = Texture2D::Create("../../testbed/assets/user/models/backpack/specular.jpg");
        
        m_Backpack = m_ActiveScene->InstantiateGameObject();

        m_DirectionalLight = {
            .Direction = glm::vec3(-1.0f, -1.0f, -1.0f),
            .Ambient = glm::vec3(0.05f, 0.05f, 0.05f),
            .Diffuse = glm::vec3(0.4f, 0.4f, 0.4f),
            .Specular = glm::vec3(0.5f, 0.5f, 0.5f)
        };

        glm::vec3 lightPositions[4] = {
            {-4.0f, +2.0f, -4.0f},
            {+4.0f, +2.0f, -4.0f},
            {+4.0f, +2.0f, +4.0f},
            {-4.0f, +2.0f, +4.0f}
        };

        for (i32 i = 0; i < 4; i++) {
            m_PointLights[i] = {
                .Position = lightPositions[i],
                .Ambient = glm::vec3(0.05f, 0.05f, 0.05f),
                .Diffuse = glm::vec3(0.8f, 0.8f, 0.8f),
                .Specular = glm::vec3(1.0f, 1.0f, 1.0f),
                .Constant = 1.0f,
                .Linear = 0.09f,
                .Quadratic = 0.032f
            };
        } 
    }

    EditorLayer::~EditorLayer() {

    }

    void EditorLayer::Update(f64 dt) {
        m_ActiveScene->Update(dt);
    }

    void EditorLayer::LateUpdate(f64 dt) {
        m_ActiveScene->LateUpdate(dt);
    }

    void EditorLayer::Render(const std::unique_ptr<Renderer>& renderer) {
        if (m_FramebufferInvalid)
            m_Framebuffer = Framebuffer::Create(m_FramebufferSpec);

        m_Framebuffer->Bind();
        glViewport(m_Viewport.Left, m_Viewport.Bottom, m_Viewport.Right, m_Viewport.Top);

        glClearColor(0.1, 0.1, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        auto litShader = m_ShaderRepository->Get("lit");
        auto lightShader = m_ShaderRepository->Get("light");

        litShader->Bind();

        // Setting Uniforms ...
        {
            litShader->SetUniformMat4("u_WorldToClipSpace", m_ActiveScene->GetCameraViewProjectionMatrix());
            litShader->SetUniformVec3("u_CameraPosition", m_ActiveScene->GetCameraPosition());

            litShader->SetUniformVec3("u_DirLight.Direction", m_DirectionalLight.Direction);
            litShader->SetUniformVec3("u_DirLight.Ambient", m_DirectionalLight.Ambient);
            litShader->SetUniformVec3("u_DirLight.Diffuse", m_DirectionalLight.Diffuse);
            litShader->SetUniformVec3("u_DirLight.Specular", m_DirectionalLight.Specular);

            litShader->SetUniformVec3("u_PointLights[0].Position", m_PointLights[0].Position);
            litShader->SetUniformVec3("u_PointLights[0].Ambient", m_PointLights[0].Ambient);
            litShader->SetUniformVec3("u_PointLights[0].Diffuse", m_PointLights[0].Diffuse);
            litShader->SetUniformVec3("u_PointLights[0].Specular", m_PointLights[0].Specular);
            litShader->SetUniformFloat("u_PointLights[0].Constant", m_PointLights[0].Constant);
            litShader->SetUniformFloat("u_PointLights[0].Linear", m_PointLights[0].Linear);
            litShader->SetUniformFloat("u_PointLights[0].Quadratic", m_PointLights[0].Quadratic);

            litShader->SetUniformVec3("u_PointLights[1].Position", m_PointLights[1].Position);
            litShader->SetUniformVec3("u_PointLights[1].Ambient", m_PointLights[1].Ambient);
            litShader->SetUniformVec3("u_PointLights[1].Diffuse", m_PointLights[1].Diffuse);
            litShader->SetUniformVec3("u_PointLights[1].Specular", m_PointLights[1].Specular);
            litShader->SetUniformFloat("u_PointLights[1].Constant", m_PointLights[1].Constant);
            litShader->SetUniformFloat("u_PointLights[1].Linear", m_PointLights[1].Linear);
            litShader->SetUniformFloat("u_PointLights[1].Quadratic", m_PointLights[1].Quadratic);

            litShader->SetUniformVec3("u_PointLights[2].Position", m_PointLights[2].Position);
            litShader->SetUniformVec3("u_PointLights[2].Ambient", m_PointLights[2].Ambient);
            litShader->SetUniformVec3("u_PointLights[2].Diffuse", m_PointLights[2].Diffuse);
            litShader->SetUniformVec3("u_PointLights[2].Specular", m_PointLights[2].Specular);
            litShader->SetUniformFloat("u_PointLights[2].Constant", m_PointLights[2].Constant);
            litShader->SetUniformFloat("u_PointLights[2].Linear", m_PointLights[2].Linear);
            litShader->SetUniformFloat("u_PointLights[2].Quadratic", m_PointLights[2].Quadratic);

            litShader->SetUniformVec3("u_PointLights[3].Position", m_PointLights[3].Position);
            litShader->SetUniformVec3("u_PointLights[3].Ambient", m_PointLights[3].Ambient);
            litShader->SetUniformVec3("u_PointLights[3].Diffuse", m_PointLights[3].Diffuse);
            litShader->SetUniformVec3("u_PointLights[3].Specular", m_PointLights[3].Specular);
            litShader->SetUniformFloat("u_PointLights[3].Constant", m_PointLights[3].Constant);
            litShader->SetUniformFloat("u_PointLights[3].Linear", m_PointLights[3].Linear);
            litShader->SetUniformFloat("u_PointLights[3].Quadratic", m_PointLights[3].Quadratic);

            litShader->SetSamplerSlot("u_Material.DiffuseMap", 0);
            litShader->SetSamplerSlot("u_Material.NormalMap", 1);
            litShader->SetSamplerSlot("u_Material.SpecularMap", 2);
        }
        //

        m_Diffuse->Bind(0);
        m_Normal->Bind(1);
        m_Specular->Bind(2);

        for (i32 i = 0; i < 5; i++) {
            m_Backpack->Transform.SetLocalPosition(glm::vec3(-10.0f + 5.0f * i, 0.0f, 0.0f));
            litShader->SetUniformMat4("u_ModelToWorldSpace", m_Backpack->Transform.WorldTransform());
            for (auto mesh : m_BackpackModel->m_Meshes) {
                renderer->DrawMesh(mesh);
            }
        }

        m_Framebuffer->Unbind();
        glViewport(m_ScreenExtents.Left, m_ScreenExtents.Bottom, m_ScreenExtents.Right, m_ScreenExtents.Top);
    }

    void EditorLayer::RenderGUI() {
        static bool dockspace_open = true;
        static bool opt_fullscreen_persistant = true;
        bool opt_fullscreen = opt_fullscreen_persistant;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

        if (opt_fullscreen) {
            ImGuiViewport* vp = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(vp->Pos);
            ImGui::SetNextWindowSize(vp->Size);
            ImGui::SetNextWindowViewport(vp->ID);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        }

        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

            ImGui::Begin("Weasel Editor", &dockspace_open, window_flags);
                
                ImGuiIO& io = ImGui::GetIO();
                if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
                    ImGui::DockSpace(ImGui::GetID("My Dockspace"), ImVec2(0.0f, 0.0f), dockspace_flags); }

                ImGui::Begin("Viewport");

                {
                    ImVec2 viewport_panel_size = ImGui::GetContentRegionAvail();
                    
                    if ((m_Viewport.Right - m_Viewport.Left) != viewport_panel_size.x * 2.0f || (m_Viewport.Top - m_Viewport.Bottom) != viewport_panel_size.y * 2.0f) {
                        m_Viewport = {0, viewport_panel_size.x * 2.0, 0, viewport_panel_size.y * 2.0};
                        m_FramebufferSpec.Width = (u32)m_Viewport.Right;
                        m_FramebufferSpec.Height = (u32)m_Viewport.Top;
                        m_ActiveScene->SetViewport(m_Viewport);
                        m_FramebufferInvalid = true;
                    }

                    ImGui::Image(
                        (void*)m_Framebuffer->GetColorAttachmentID(),
                        viewport_panel_size,
                        ImVec2{0, 1}, ImVec2{1, 0}
                    );
                }
                
                ImGui::End();

                ImGui::Begin("Settings");
                
                {

                }
                
                ImGui::End();

                ImGui::Begin("More Settings");
                
                {

                }
                
                ImGui::End();

            ImGui::End();

        ImGui::End();
    }

    bool EditorLayer::OnEvent(Event& e) {
        switch (e.Tag) {
            case EventTag::WindowFramebufferSizeEvent:
                m_ScreenExtents.Right = (f32)e.WindowFramebufferSizeEvent.Width;
                m_ScreenExtents.Top = (f32)e.WindowFramebufferSizeEvent.Height;
                break;
            default:
                break;
        }
        return false;
    }
}