#pragma once

#include "Weasel/Core/GameObject.hpp"
#include "Weasel/Core/Scene.hpp"

#include "Weasel/Base/Base.hpp"

#include "Weasel/Graphics/Cameras.hpp"

namespace Weasel {
    class VirtualCamera : public Component {
        public:
            VirtualCamera(GameObject* owner);
            ~VirtualCamera();
            void MakeActive();
            virtual void LateUpdate(f64 dt) override;
            virtual void OnViewportResize(Rect2D viewport) override;

            void SetFOV();
            void SetNearClip();
            void SetFarClip();
        private:
            f32 m_FOV = 60.0f;
            f32 m_NearClip = 0.1f;
            f32 m_FarClip = 1000.0f;
            std::shared_ptr<Camera> m_Camera;
    };
}