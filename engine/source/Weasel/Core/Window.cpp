#include "Weasel/Core/Window.hpp"

namespace Weasel
{
    std::unique_ptr<Window> Window::Create(const WindowSpec &spec)
    {
        return std::make_unique<Window>(spec);
    }

    Window::Window(const WindowSpec &spec)
    {
        Init(spec);
    }

    Window::~Window()
    {
        Shutdown();
    }

    void Window::Init(const WindowSpec &spec)
    {
        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        LOG_INFO("Platform Detected: MacOS, enabling OpenGL forward compat");
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);


        m_WindowHandle = glfwCreateWindow(spec.Width, spec.Height, spec.Title, NULL, NULL);

        m_WindowState.Title = spec.Title;
        m_WindowState.Width = spec.Width;
        m_WindowState.Height = spec.Height;
        glfwGetFramebufferSize(m_WindowHandle, &m_WindowState.FramebufferWidth, &m_WindowState.FramebufferHeight);

        glfwSetWindowUserPointer(m_WindowHandle, &m_WindowState);

        glfwMakeContextCurrent(m_WindowHandle);
        glfwSwapInterval(0);
        gladLoadGL();
        glClearColor(0.1, 0.1, 0.1, 1.0);

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(m_WindowHandle, true);
        ImGui_ImplOpenGL3_Init("#version 410 core");

        glfwSetWindowCloseCallback(m_WindowHandle, [](GLFWwindow *window)
        {
            auto state = (WindowState*)glfwGetWindowUserPointer(window);
            Event e = {EventTag::WindowCloseEvent};
            if (!state->EventCallback(e)) {
                glfwSetWindowShouldClose(window, GLFW_FALSE);
            } 
        });

        glfwSetWindowSizeCallback(m_WindowHandle, [](GLFWwindow *window, i32 width, i32 height)
        {
            auto state = (WindowState*)glfwGetWindowUserPointer(window);
            Event e = {EventTag::WindowSizeEvent};
            e.WindowSizeEvent = {width, height};
            state->EventCallback(e);
        });

        glfwSetFramebufferSizeCallback(m_WindowHandle, [](GLFWwindow *window, i32 width, i32 height)
        {
            auto state = (WindowState*)glfwGetWindowUserPointer(window);
            Event e = {EventTag::WindowFramebufferSizeEvent};
            e.WindowFramebufferSizeEvent = {width, height};
            state->EventCallback(e);
        });
    }

    void Window::Shutdown()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwDestroyWindow(m_WindowHandle);
        glfwTerminate();
    }

    void Window::Update(f64 dt)
    {
        glfwSwapBuffers(m_WindowHandle);
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}
