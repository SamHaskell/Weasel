#include "Weasel/Components/EditorCameraController.hpp"

namespace Weasel {
    EditorCameraController::EditorCameraController(GameObject* owner) : Component(owner) {

    }

    EditorCameraController::~EditorCameraController() {

    }

    void EditorCameraController::Awake() {
        Input::DisableCursor();
    }

    void EditorCameraController::Update(f64 dt) {
        // Move Position
        if (Input::IsKeyDown(WEASEL_KEY_W)) {
            m_Owner->Transform.Translate(m_Owner->Transform.Forward() * MoveSpeed * (f32)dt); }
        if (Input::IsKeyDown(WEASEL_KEY_S)) {
            m_Owner->Transform.Translate(-m_Owner->Transform.Forward() * MoveSpeed * (f32)dt); }

        if (Input::IsKeyDown(WEASEL_KEY_A)) {
            m_Owner->Transform.Translate(-m_Owner->Transform.Right() * MoveSpeed * (f32)dt); }

        if (Input::IsKeyDown(WEASEL_KEY_D)) {
            m_Owner->Transform.Translate(m_Owner->Transform.Right() * MoveSpeed * (f32)dt); }

        // Move Rotation
        Point2D mouseDelta = Input::MousePosition() - m_PreviousMousePosition;
        m_PreviousMousePosition = Input::MousePosition();

        m_Owner->Transform.Rotate(glm::vec3(0.0f, 1.0f, 0.0f), mouseDelta.X/1280.0 * -HorizontalLookSensitivity);
        m_Owner->Transform.Rotate(glm::vec3(1.0f, 0.0f, 0.0f), mouseDelta.Y/720.0 * -VerticalLookSensitivity);

        LOG_DEBUG("%s", mouseDelta.ToString().c_str());
    }
}