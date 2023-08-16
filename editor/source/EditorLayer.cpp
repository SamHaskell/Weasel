#include "EditorLayer.hpp"

EditorLayer::EditorLayer() {

}

EditorLayer::~EditorLayer() {

}

void EditorLayer::Update(f64 dt) {

}

void EditorLayer::LateUpdate(f64 dt) {

}

void EditorLayer::ImGuiRender() {
    ImGui::Begin("Test Window");
    ImGui::ColorEdit4("A Color Picker!", glm::value_ptr(m_TestColor));
}

void EditorLayer::Render(const std::unique_ptr<Weasel::Renderer>& renderer) {

}

bool EditorLayer::OnEvent(Weasel::Event& e) {
    return false;
}