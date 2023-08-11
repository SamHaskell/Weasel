#pragma once

#include "Weasel/Base/Base.hpp"
#include "Weasel/Events/Events.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

namespace Weasel
{
    struct WindowSpec
    {
        const char* Title = "Weasel App";
        i32 Width = 1280;
        i32 Height = 720;
    };

    struct WindowState
    {
        const char* Title;
        i32 Width;
        i32 Height;
        i32 FramebufferWidth;
        i32 FramebufferHeight;
        std::function<bool(Event&)> EventCallback;
    };

    class Window
    {
    public:
        static std::unique_ptr<Window> Create(const WindowSpec& spec);
        Window(const WindowSpec& spec);
        ~Window();
        void Update();
        inline void SetEventCallback(const std::function<bool(Event&)>& callback) { m_WindowState.EventCallback = callback; };
        inline void SetClearColor(f64 r, f64 g, f64 b, f64 a) { glClearColor(r, g, b, a); }
        inline f32 GetAspectRatio() { return (f32)m_WindowState.Width/(f32)m_WindowState.Height; }
    private:
        WindowState m_WindowState;
        GLFWwindow* m_WindowHandle;
        bool m_ShowDemo = true;
        void Init(const WindowSpec& spec);
        void Shutdown();
    };
}