#include "Weasel/Core/Application.hpp"
#include "Weasel/Core/Entrypoint.hpp"

#include "TestLayer.hpp"

class Testbed : public Weasel::Application {
    public:
        Testbed(Weasel::AppConfig config) : Weasel::Application(config) {
            m_AppStack.AddLayer(new TestLayer(m_AppState));
        }
        ~Testbed() {}
};

Weasel::Application *Weasel::CreateApplication() {
    Weasel::AppConfig config = {
        .Name = "Weasel Runtime Test",
        .InitWidth = 1280,
        .InitHeight = 720
    };

    return new Testbed(config);
}