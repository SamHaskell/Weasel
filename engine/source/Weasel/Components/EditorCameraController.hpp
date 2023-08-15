#pragma once

#include "Weasel/Core/GameObject.hpp"
#include "Weasel/Base/Base.hpp"
#include "Weasel/Input/Input.hpp"

namespace Weasel {
    class EditorCameraController : public Component {
        public:
            EditorCameraController(GameObject* owner);
            ~EditorCameraController() override;
            void Awake() override;
            void Update(f64 dt) override;
            f32 MoveSpeed = 5.0f;
            f32 HorizontalLookSensitivity = 180.0f;
            f32 VerticalLookSensitivity = 180.0f;
        private:
            bool m_Captured;
            bool m_InitFrame;
            f64 m_RotationX;
            f64 m_RotationY;
            Point2D m_PreviousMousePosition;
    };
}