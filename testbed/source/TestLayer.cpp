#include "TestLayer.hpp"

TestLayer::TestLayer() {
    m_ActiveScene = Weasel::Scene::Create();

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

    m_ShaderRepository = Weasel::ShaderRepository::Create();
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
    auto editorVCamera = editorCamera->AddComponent<Weasel::VirtualCamera>();
    auto editorCameraController = editorCamera->AddComponent<Weasel::EditorCameraController>();

    editorVCamera->MakeActive();
    editorCamera->Transform.SetLocalPosition(glm::vec3(6.0f, 0.0f, 6.0f));
    auto fwd = glm::normalize(glm::vec3(-1.0f, 0.0f, -1.0f));
    editorCamera->Transform.SetLocalRotation(glm::quatLookAt(fwd, glm::vec3(0.0f, 1.0f, 0.0f)));

    auto cubeMesh = Weasel::Mesh::Create(cubeVertices, cubeIndices);
    auto cubeMaterial = Weasel::Material::Create();
    
    m_Cube = m_ActiveScene->InstantiateGameObject();
    auto cubeMeshInstance = m_Cube->AddComponent<Weasel::MeshInstance>();
    cubeMeshInstance->SetMesh(cubeMesh);
    cubeMeshInstance->SetMaterial(cubeMaterial);

    m_BackpackModel = Weasel::Model::Load("../../testbed/assets/user/models/backpack/backpack.obj");
    m_Diffuse = Weasel::Texture2D::Create("../../testbed/assets/user/models/backpack/diffuse.jpg");
    m_Normal = Weasel::Texture2D::Create("../../testbed/assets/user/models/backpack/normal.png");
    m_Specular = Weasel::Texture2D::Create("../../testbed/assets/user/models/backpack/specular.jpg");

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

TestLayer::~TestLayer() {

}

void TestLayer::Update(f64 dt) {
    m_ActiveScene->Update(dt);
}

void TestLayer::LateUpdate(f64 dt) {
    m_ActiveScene->LateUpdate(dt);
}

void TestLayer::Render(const std::unique_ptr<Weasel::Renderer>& renderer) {
    auto litShader = m_ShaderRepository->Get("lit");
    auto lightShader = m_ShaderRepository->Get("light");

    litShader->Bind();
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

    m_Diffuse->Bind(0);
    m_Normal->Bind(1);
    m_Specular->Bind(2);

    for (i32 i = 0; i < 5; i++) {
        m_Cube->Transform.SetLocalPosition(glm::vec3(-10.0f + 5.0f * i, 0.0f, 0.0f));
        litShader->SetUniformMat4("u_ModelToWorldSpace", m_Cube->Transform.WorldTransform());
        for (auto mesh : m_BackpackModel->m_Meshes) {
            renderer->DrawMesh(mesh, m_Cube->GetComponent<Weasel::MeshInstance>()->GetMaterial());
        }
    }

    lightShader->Bind();
    lightShader->SetUniformMat4("u_WorldToClipSpace", m_ActiveScene->GetCameraViewProjectionMatrix());
    lightShader->SetUniformVec3("u_ObjectColor", glm::vec3(1.0f, 1.0f, 1.0f));

    for (i32 i = 0; i < 4; i++) { 
        lightShader->SetUniformMat4("u_ModelToWorldSpace", glm::scale(glm::translate(glm::mat4(1.0f), m_PointLights[i].Position), glm::vec3(0.2f, 0.2f, 0.2f)));
        m_Cube->GetComponent<Weasel::MeshInstance>()->GetMesh()->Draw(); }
}

void TestLayer::ImGuiRender() {

}

bool TestLayer::OnEvent(Weasel::Event& e) {
    m_ActiveScene->OnEvent(e);
    return false;
}