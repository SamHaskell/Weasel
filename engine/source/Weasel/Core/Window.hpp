#pragma once

#include "Weasel/Base/Base.hpp"
#include "Weasel/Events/Events.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Weasel
{
    struct WindowConfig
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
        static std::unique_ptr<Window> Create(const WindowConfig& config);
        Window(const WindowConfig& config);
        ~Window();
        void Update(f64 dt);
        inline void SetEventCallback(const std::function<bool(Event&)>& callback) { m_WindowState.EventCallback = callback; };
        inline void SetClearColor(f64 r, f64 g, f64 b, f64 a) { glClearColor(r, g, b, a); }
        inline f32 GetAspectRatio() { return (f32)m_WindowState.Width/(f32)m_WindowState.Height; }
        inline void* GetNativeHandle() const { return m_WindowHandle; }
        inline u32 GetFramebufferWidth() { return m_WindowState.FramebufferWidth; }
        inline u32 GetFramebufferHeight() { return m_WindowState.FramebufferHeight; }
    private:
        WindowState m_WindowState;
        GLFWwindow* m_WindowHandle;
        bool m_ShowDemo = true;
        void Init(const WindowConfig& config);
        void Shutdown();
    };
}