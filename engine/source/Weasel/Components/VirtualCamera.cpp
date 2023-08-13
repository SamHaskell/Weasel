#include "Weasel/Components/VirtualCamera.hpp"

namespace Weasel {
    VirtualCamera::VirtualCamera(GameObject* owner) : Component(owner) {
        // m_Owner->Scene;
        // m_Camera = Camera::CreatePerspective();
    }

    VirtualCamera::~VirtualCamera() {

    }

    void VirtualCamera::MakeActive() {
        m_Owner->Scene->SetMainCamera(m_Camera);
    }

    void VirtualCamera::Update(f64 dt) {
        LOG_INFO("Updating!");
        m_Camera->SetPerspectiveProjection(FOV, AspectRatio, NearClip, FarClip);
    }
}