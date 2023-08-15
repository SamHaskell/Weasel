#pragma once

#include "Weasel/Core/GameObject.hpp"
#include "Weasel/Base/Base.hpp"
#include "Weasel/Input/Input.hpp"

namespace Weasel {
    class EditorCameraController : public Component {
        public:
            EditorCameraController(GameObject* owner);
            ~EditorCameraController() override;
            void Update(f64 dt) override;
            f32 MoveSpeed = 3.0f;
            f32 HorizontalLookSensitivity = 90.0f;
            f32 VerticalLookSensitivity = 90.0f;
        private:

    };
}