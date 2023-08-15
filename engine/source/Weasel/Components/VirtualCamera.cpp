#include "Weasel/Components/VirtualCamera.hpp"

namespace Weasel {
    VirtualCamera::VirtualCamera(GameObject* owner) : Component(owner) {
        m_Camera = std::make_shared<Camera>();
        m_Camera->SetPerspectiveProjection(
            60.0f,
            m_Owner->CurrentScene->AspectRatio,
            0.1f,
            1000.0f
        );
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

    void VirtualCamera::OnWindowFramebufferResize(i32 width, i32 height) {
        LOG_DEBUG("On resize!");
        m_Camera->SetPerspectiveProjection(m_FOV, (f32)width/(f32)height, m_NearClip, m_FarClip);
    }
}