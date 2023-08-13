#include "Weasel/Core/Scene.hpp"

namespace Weasel {
    std::unique_ptr<Scene> Scene::Create() {
        return std::make_unique<Scene>();
    }
    Scene::Scene() {
        m_GameObjects.reserve(INITIAL_SCENE_OBJECT_CAPACITY);
    }

    Scene::~Scene() {

    }

    std::shared_ptr<GameObject> Scene::InstantiateGameObject() {
        auto go = std::make_shared<GameObject>(this);
        m_GameObjects.push_back(go);
        return go;
    }

    void Scene::Update(f64 dt) {
        for (auto& go : m_GameObjects) {
            go->Update(dt);
        }
    }

    void Scene::OnEvent(Event &e) {
        switch (e.Tag) {
            case EventTag::WindowSizeEvent:
                AspectRatio = (f32)e.WindowSizeEvent.Width / (f32)e.WindowSizeEvent.Width;
                break;
            default:
                break;
        }

        for (auto& go : m_GameObjects) {
            go->OnEvent(e);
        }
    }
}