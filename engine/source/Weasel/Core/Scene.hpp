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
            void Awake();
            void Update(f64 dt);
            void LateUpdate(f64 dt);
            inline void SetMainCamera(std::shared_ptr<Camera> camera) { m_MainCamera = camera; }
            void SetViewport(Rect2D viewport);
            void OnEvent(Event &e);

            // TEMPORARY ... NEED TO COME UP WITH A NICE WAY TO HANDLE CAMERAS AND CAMERA DATA

            inline glm::mat4 GetCameraViewProjectionMatrix() { return m_MainCamera->ViewProjectionMatrix(); }
            inline glm::vec3 GetCameraPosition() { return m_MainCamera->Position(); }
            inline glm::vec3 GetCameraForward() { return m_MainCamera->Forward(); }

        private:
            f32 AspectRatio;
            std::shared_ptr<Camera> m_MainCamera;
            std::vector<std::shared_ptr<GameObject>> m_GameObjects;
    };
}