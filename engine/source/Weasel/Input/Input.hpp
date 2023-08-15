#pragma once

#include "Weasel/Base/Base.hpp"
#include "Weasel/Events/Events.hpp"
#include "Weasel/Core/Window.hpp"

#include "Weasel/Input/Keys.hpp"

namespace Weasel {
    class Input {
        public:
            static void SetActiveWindow(const std::unique_ptr<Window>& window);
            static bool IsKeyDown(i32 key);
            static Point2D MousePosition();
            static Point2D MouseDelta();
            inline static void DisableCursor() { glfwSetInputMode(s_NativeWindowHandle, GLFW_CURSOR, GLFW_CURSOR_DISABLED); }
        private:
            static GLFWwindow* s_NativeWindowHandle;
    };
}