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
            m_Owner->Transform.WorldForward(),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );
    }

    VirtualCamera::~VirtualCamera() {

    }

    void VirtualCamera::MakeActive() {
        m_Owner->CurrentScene->SetMainCamera(m_Camera);
    }

    void VirtualCamera::Update(f64 dt) {
        LOG_INFO("Updating!");
    }
}