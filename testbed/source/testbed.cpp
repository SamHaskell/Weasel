// #include <Wigner.hpp>

#include "Weasel/Core/Application.hpp"
#include "Weasel/Core/Entrypoint.hpp"

#include <iostream>

class Testbed : public Weasel::Application {
    public:
        Testbed() {}
        ~Testbed() {}
    private:
};

Weasel::Application *Weasel::CreateApplication() {
    return new Testbed();
}