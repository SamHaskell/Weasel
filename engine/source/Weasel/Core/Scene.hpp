#pragma once

#include "Weasel/Base/Base.hpp"
#include "Weasel/Events/Events.hpp"
#include "Weasel/Core/GameObject.hpp"
#include "Weasel/Graphics/Renderer.hpp"
#include "Weasel/Graphics/Cameras.hpp"
#include "Weasel/Graphics/Lights.hpp"

namespace Weasel {
    
    #define INITIAL_SCENE_OBJECT_CAPACITY 2048

    class Scene {
        public:
            static std::unique_ptr<Scene> Create();
            Scene();
            ~Scene();
            std::shared_ptr<GameObject> InstantiateGameObject();
            void Update(f64 dt);
            inline void SetMainCamera(std::shared_ptr<Camera> camera) { m_MainCamera = camera; }
            void OnEvent(Event &e);

        private:
            std::shared_ptr<Camera> m_MainCamera;
            std::vector<std::shared_ptr<GameObject>> m_GameObjects;
    };
}