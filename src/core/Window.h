#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

struct WindowProperties {
    std::string title;
    int         width, height;

    WindowProperties(
        std::string title = "Photons Application", int width = 800,
        int height = 600)
        : title(title), width(width), height(height)
    {
    }
};

namespace Photons
{
    class Window
    {
    public:
        Window(const WindowProperties &props);
        ~Window();

        void Update();

        bool ShouldClose() const;

        GLFWwindow *GetNativeHandle() const;

    private:
        static void FrameBufferCallback(GLFWwindow *window, int width,
                                        int height);
        void        ProcessInput();

    private:
        WindowProperties m_props;

        GLFWwindow *m_window;
    };

    inline bool Window::ShouldClose() const
    {
        return glfwWindowShouldClose(m_window);
    }

    inline GLFWwindow *Window::GetNativeHandle() const { return m_window; }

    inline void Window::FrameBufferCallback(
        GLFWwindow *window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }
} // namespace Photons
