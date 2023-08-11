#pragma once

#include "Weasel/Core/Application.hpp"

extern Weasel::Application *Weasel::CreateApplication();

int main(int argc, char **argv) {
    auto app = Weasel::CreateApplication();
    if (!app->Run()) {
    }
    delete app;
}