#pragma once

namespace Wigner
{
    class Application
    {
    public:
        Application();
        virtual ~Application();
        bool Run();
    private:
    };

    Application *CreateApplication();
}