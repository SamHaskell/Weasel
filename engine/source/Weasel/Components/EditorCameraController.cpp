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

        if (Input::IsKeyDown(WEASEL_KEY_ESCAPE)) {
            Input::EnableCursor();
            m_Captured = false;
            m_InitFrame = true;
        }

        if (Input::IsKeyDown(WEASEL_KEY_SPACE)) { Input::DisableCursor(); m_Captured = true; }

        if (m_Captured) {
            m_InitFrame = false;
            
            Point2D mouseDelta = (m_InitFrame) ? Point2D(0.0, 0.0) : Input::MousePosition() - m_PreviousMousePosition;
            m_RotationX = Maths::Clamp(m_RotationX + mouseDelta.Y * VerticalLookSensitivity/720.0, -89.9, 89.9);
            m_RotationY = Maths::Wrap(m_RotationY + (mouseDelta.X * HorizontalLookSensitivity/1280.0), -180.0, 360.0);
            m_Owner->Transform.SetLocalRotation(glm::quat(glm::vec3(-glm::radians(m_RotationX), -glm::radians(m_RotationY), 0.0)));

            if (Input::IsKeyDown(WEASEL_KEY_W)) {
                m_Owner->Transform.Translate(+ m_Owner->Transform.Forward() * MoveSpeed * (f32)dt); }
            if (Input::IsKeyDown(WEASEL_KEY_S)) {
                m_Owner->Transform.Translate(- m_Owner->Transform.Forward() * MoveSpeed * (f32)dt); }
            if (Input::IsKeyDown(WEASEL_KEY_A)) {
                m_Owner->Transform.Translate(- m_Owner->Transform.Right() * MoveSpeed * (f32)dt); }
            if (Input::IsKeyDown(WEASEL_KEY_D)) {
                m_Owner->Transform.Translate(+ m_Owner->Transform.Right() * MoveSpeed * (f32)dt); }
            if (Input::IsKeyDown(WEASEL_KEY_E)) {
                m_Owner->Transform.Translate(+ m_Owner->Transform.Up() * MoveSpeed * (f32)dt); }
            if (Input::IsKeyDown(WEASEL_KEY_Q)) {
                m_Owner->Transform.Translate(- m_Owner->Transform.Up() * MoveSpeed * (f32)dt); }
        }
        m_PreviousMousePosition = Input::MousePosition();
    }
}