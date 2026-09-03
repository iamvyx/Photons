#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace Photons
{
    enum SHADER_TYPE {
        VERTEX   = GL_VERTEX_SHADER,
        FRAGMENT = GL_FRAGMENT_SHADER
    };

    struct Shader {
    public:
        Shader(const char *source, SHADER_TYPE type);

        void Compile();

        inline GLuint Get() const { return m_id; }

    private:
        GLuint m_id;

        const char *m_source;
        SHADER_TYPE m_type;
    };

    inline Shader::Shader(
        const char *source, SHADER_TYPE type)
        : m_source(source), m_type(type)
    {
        m_id = glCreateShader(type);
        glShaderSource(m_id, 1, &m_source, NULL);
    }

    inline void Shader::Compile()
    {
        glCompileShader(m_id);

        int  success;
        char info[1024];
        glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(m_id, 1024, NULL, info);
            std::cerr << "ERROR::SHADER:COMPILATION\n" << info;
            exit(1);
        }
    }
} // namespace Photons
