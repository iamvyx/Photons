#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Photons
{
    class Renderer
    {
    public:
        Renderer();
        ~Renderer();

        // It will be reformulated at a later stage.
        void Update();

    private:
        GLuint m_program;
        GLuint m_vertexbuffer;
        GLuint m_vertexarray;
        GLuint m_elementarray;
    };
} // namespace Photons
