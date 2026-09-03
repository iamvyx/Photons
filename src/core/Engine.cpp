#include "Engine.h"

#include <iostream>

namespace Photons
{
    Engine::Engine()
    {
        if (!glfwInit()) {
            std::cerr << "Can't initialize GLFW!\n";
            exit(1);
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_window = new Window({});

        if (!gladLoadGLLoader(
                reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
            std::cerr << "Can't initialize GLAD";
            exit(1);
        }

        m_renderer = new Renderer();

        while (!m_window->ShouldClose()) {
            glfwPollEvents();

            m_renderer->Update();

            m_window->Update();
        }
    }

    Engine::~Engine()
    {
        delete m_window;
        delete m_renderer;
    }
} // namespace Photons
