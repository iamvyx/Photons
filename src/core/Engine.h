#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Window.h"

#include <renderer/Renderer.h>

namespace Photons
{
    class Engine
    {
    public:
        Engine();
        ~Engine();

    private:
        Window   *m_window;
        Renderer *m_renderer;
    };
} // namespace Photons
