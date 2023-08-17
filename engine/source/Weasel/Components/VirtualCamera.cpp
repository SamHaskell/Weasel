#include "Weasel/Components/VirtualCamera.hpp"

namespace Weasel {
    VirtualCamera::VirtualCamera(GameObject* owner) : Component(owner) {
        m_Camera = std::make_shared<Camera>();
        m_Camera->SetViewDirection(
            m_Owner->Transform.WorldPosition(),
            m_Owner->Transform.Forward(),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );
    }

    VirtualCamera::~VirtualCamera() {

    }

    void VirtualCamera::MakeActive() {
        m_Owner->CurrentScene->SetMainCamera(m_Camera);
    }
    
    void VirtualCamera::LateUpdate(f64 dt) {
        m_Camera->SetViewDirection(
            m_Owner->Transform.WorldPosition(),
            m_Owner->Transform.Forward(),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );
    }

    void VirtualCamera::OnViewportResize(Rect2D viewport) {
        f32 aspect = (viewport.Right - viewport.Left) / (viewport.Top - viewport.Bottom);
        m_Camera->SetPerspectiveProjection(m_FOV, aspect, m_NearClip, m_FarClip);
    }
}