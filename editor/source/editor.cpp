#include "Weasel/Core/Application.hpp"
#include "Weasel/Core/Entrypoint.hpp"

#include "EditorLayer.hpp"

namespace Weasel {
    class Editor : public Application {
        public:
            Editor(AppConfig config) : Application(config) {
                m_AppStack.AddOverlay(new EditorLayer(m_AppState));
            }
            ~Editor() {}
        private:
    };

    Application *CreateApplication() {
        AppConfig config = {
            .Name = "Weasel Editor",
            .InitWidth = 1280,
            .InitHeight = 720
        };
        return new Editor(config);
    }
}