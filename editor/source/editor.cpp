#include "Weasel/Core/Application.hpp"
#include "Weasel/Core/Entrypoint.hpp"

#include "EditorLayer.hpp"

class Editor : public Weasel::Application {
    public:
        Editor() {
            m_AppStack.AddOverlay(new EditorLayer());
        }
        ~Editor() {}
    private:
};

Weasel::Application *Weasel::CreateApplication() {
    return new Editor();
}