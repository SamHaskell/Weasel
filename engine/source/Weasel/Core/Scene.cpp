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

    void Scene::Awake() {
        for (auto& go : m_GameObjects) {
            go->Awake();
        }
    }

    void Scene::Update(f64 dt) {
        for (auto& go : m_GameObjects) {
            go->Update(dt);
        }
    }

    void Scene::LateUpdate(f64 dt) {
        for (auto& go : m_GameObjects) {
            go->LateUpdate(dt);
        }
    }

    void Scene::SetViewport(Rect2D viewport) { 
        AspectRatio = (viewport.Right - viewport.Left) / (viewport.Top - viewport.Bottom);
        for (auto& go : m_GameObjects) {
            go->OnViewportResize(viewport);
        }
    }

    void Scene::OnEvent(Event &e) {
        for (auto& go : m_GameObjects) {
            go->OnEvent(e);
        }
    }
}