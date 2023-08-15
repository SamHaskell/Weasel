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
        LOG_DEBUG("(%f, %f, %f)", m_Owner->Transform.LocalEulerAngles().x, m_Owner->Transform.LocalEulerAngles().y, m_Owner->Transform.LocalEulerAngles().z);

        // Move Position
        if (Input::IsKeyDown(WEASEL_KEY_W)) {
            m_Owner->Transform.Translate(m_Owner->Transform.Forward() * MoveSpeed * (f32)dt); }
        if (Input::IsKeyDown(WEASEL_KEY_S)) {
            m_Owner->Transform.Translate(-m_Owner->Transform.Forward() * MoveSpeed * (f32)dt); }
        if (Input::IsKeyDown(WEASEL_KEY_A)) {
            m_Owner->Transform.Translate(-m_Owner->Transform.Right() * MoveSpeed * (f32)dt); }
        if (Input::IsKeyDown(WEASEL_KEY_D)) {
            m_Owner->Transform.Translate(m_Owner->Transform.Right() * MoveSpeed * (f32)dt); }
        if (Input::IsKeyDown(WEASEL_KEY_Q)) {
            m_RotationY -= HorizontalLookSensitivity * dt; }
        if (Input::IsKeyDown(WEASEL_KEY_E)) {
            m_RotationY += HorizontalLookSensitivity * dt; }

        // Move Rotation
        Point2D mouseDelta = Input::MousePosition() - m_PreviousMousePosition;
        m_PreviousMousePosition = Input::MousePosition();

        m_RotationX = Maths::Clamp(m_RotationX + mouseDelta.Y * VerticalLookSensitivity/720.0, -89.9, 89.9);
        m_RotationY = Maths::Wrap(m_RotationY + (mouseDelta.X * HorizontalLookSensitivity/1280.0), -180.0, 360.0);

        LOG_DEBUG("(%f, %f)", m_RotationY, m_RotationX);

        m_Owner->Transform.SetLocalRotation(glm::quat(glm::vec3(-glm::radians(m_RotationX), -glm::radians(m_RotationY), 0.0)));
    }
}