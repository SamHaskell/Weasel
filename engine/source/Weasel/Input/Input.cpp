#include "Weasel/Input/Input.hpp"

namespace Weasel {
    GLFWwindow* Input::s_NativeWindowHandle;

    void Input::SetActiveWindow(const std::unique_ptr<Window>& window) {
        s_NativeWindowHandle = (GLFWwindow*)window->GetNativeHandle();
    }

    bool Input::IsKeyDown(i32 key) {
        if (s_NativeWindowHandle) {
            auto state = glfwGetKey(s_NativeWindowHandle, key);
            return (state == GLFW_PRESS || state == GLFW_REPEAT);
        }
        LOG_WARN("Polling for input without a bound Window.");
        return false;
    }

    Point2D Input::MousePosition() {
        Point2D point;
        glfwGetCursorPos(s_NativeWindowHandle, &point.X, &point.Y);
        return point;
    }
}