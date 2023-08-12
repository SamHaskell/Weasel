#include "Weasel/Core/Scene.hpp"

namespace Weasel {
    Scene::Scene() {
        m_GameObjects.reserve(INITIAL_SCENE_OBJECT_CAPACITY);
    }

    Scene::~Scene() {

    }

    std::shared_ptr<GameObject> Scene::InstantiateGameObject() {
        auto go = std::make_shared<GameObject>();
        m_GameObjects.push_back(go);
        return go;
    }
}