// #include <Wigner.hpp>

#include "Wigner/Core/Application.hpp"
#include "Wigner/Core/Entrypoint.hpp"

#include <iostream>

class Testbed : public Wigner::Application {
    public:
        Testbed() {}
        ~Testbed() {}
    private:
};

Wigner::Application *Wigner::CreateApplication() {
    return new Testbed();
}