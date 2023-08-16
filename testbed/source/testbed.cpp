#include "Weasel/Core/Application.hpp"
#include "Weasel/Core/Entrypoint.hpp"

#include "TestLayer.hpp"

class Testbed : public Weasel::Application {
    public:
        Testbed() {
            m_AppStack.AddLayer(new TestLayer());
        }
        ~Testbed() {}
};

Weasel::Application *Weasel::CreateApplication() {
    return new Testbed();
}