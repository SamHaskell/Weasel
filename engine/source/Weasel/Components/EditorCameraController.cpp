#include "Weasel/Components/EditorCameraController.hpp"

namespace Weasel {
    EditorCameraController::EditorCameraController(GameObject* owner) : Component(owner) {

    }

    EditorCameraController::~EditorCameraController() {

    }

    void EditorCameraController::Update(f64 dt) {
        
        // Move Position
        if (Input::IsKeyDown(WEASEL_KEY_W)) {
            m_Owner->Transform.Translate(m_Owner->Transform.Forward() * MoveSpeed * (f32)dt);
        }

        if (Input::IsKeyDown(WEASEL_KEY_S)) {
            m_Owner->Transform.Translate(-m_Owner->Transform.Forward() * MoveSpeed * (f32)dt);
        }

        if (Input::IsKeyDown(WEASEL_KEY_A)) {
            m_Owner->Transform.Translate(-m_Owner->Transform.Right() * MoveSpeed * (f32)dt);
        }

        if (Input::IsKeyDown(WEASEL_KEY_D)) {
            m_Owner->Transform.Translate(m_Owner->Transform.Right() * MoveSpeed * (f32)dt);
        }     

        // Move Rotation
    }
}