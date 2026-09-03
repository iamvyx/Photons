#include "Window.h"

#include <iostream>

namespace Photons
{
    Window::Window(
        const WindowProperties &props)
        : m_props(props)
    {
        m_window = glfwCreateWindow(m_props.width, m_props.height,
                                    m_props.title.c_str(), NULL, NULL);
        if (!m_window) {
            std::cerr << "Can't create Window!\n";
            exit(1);
        }
        glfwMakeContextCurrent(m_window);
        glfwSetFramebufferSizeCallback(m_window, FrameBufferCallback);
    }

    Window::~Window() { glfwDestroyWindow(m_window); }

    void Window::Update()
    {
        glfwSwapBuffers(m_window);
        ProcessInput();
    }

    void Window::ProcessInput()
    {
        if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(m_window, GLFW_TRUE);

        if (glfwGetKey(m_window, GLFW_KEY_CAPS_LOCK) == GLFW_PRESS) {
            glfwWaitEventsTimeout(0.5);

            GLint mode[2];
            glGetIntegerv(GL_POLYGON_MODE, mode);

            if (mode[0] == GL_FILL || mode[1] == GL_FILL) {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            } else {
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }

            glfwWaitEventsTimeout(0.5);
        }
    }

} // namespace Photons
