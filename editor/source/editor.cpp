#include "Weasel/Core/Application.hpp"
#include "Weasel/Core/Entrypoint.hpp"

class Editor : public Weasel::Application {
    public:
        Editor() {}
        ~Editor() {}
    private:
};

Weasel::Application *Weasel::CreateApplication() {
    return new Editor();
}