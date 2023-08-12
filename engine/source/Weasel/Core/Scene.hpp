#pragma once

#include "Weasel/Base/Base.hpp"
#include "Weasel/Core/GameObject.hpp"
#include "Weasel/Graphics/Cameras.hpp"
#include "Weasel/Graphics/Lights.hpp"

namespace Weasel {
    
    #define INITIAL_SCENE_OBJECT_CAPACITY 2048

    class Scene {
        public:
            Scene();
            ~Scene();
            std::shared_ptr<GameObject> InstantiateGameObject();

        private:
            std::vector<std::shared_ptr<GameObject>> m_GameObjects;
    };
}