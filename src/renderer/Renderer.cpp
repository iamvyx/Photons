#include "Renderer.h"

#include "Shader.h"

static const char *vertex_shader_src = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;

    void main()
    {
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    }
)";

static const char *fragment_shader_src = R"(
    #version 330 core
    out vec4 FragColor;

    void main()
    {
        FragColor = vec4(1.0f, 0.5f, 0.0f, 0.1f);
    } 
)";

namespace Photons
{

    Renderer::Renderer()
    {
        Shader vertex(vertex_shader_src, SHADER_TYPE::VERTEX);
        Shader fragment(fragment_shader_src, SHADER_TYPE::FRAGMENT);

        vertex.Compile();
        fragment.Compile();

        m_program = glCreateProgram();
        glAttachShader(m_program, vertex.Get());
        glAttachShader(m_program, fragment.Get());
        glLinkProgram(m_program);

        glDeleteShader(vertex.Get());
        glDeleteShader(fragment.Get());

        glGenVertexArrays(1, &m_vertexarray);

        glGenBuffers(1, &m_vertexbuffer);
        glGenBuffers(1, &m_elementarray);

        glBindVertexArray(m_vertexarray);

        GLfloat vertices[] = {
            -0.5f, 0.5f,  0.0f, // Top Left
            0.5f,  0.5f,  0.0f, // Top Right
            -0.5f, -0.5f, 0.0f, // Bottom left
            0.5f,  -0.5f, 0.0f, // Bottom Right
        };

        GLuint indices[] = { 0, 1, 2, 1, 2, 3 };

        glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
                     GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementarray);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                     GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                              (void *)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glBindVertexArray(0);
    }

    Renderer::~Renderer()
    {
        glDeleteProgram(m_program);
        glDeleteVertexArrays(1, &m_vertexarray);

        glDeleteBuffers(1, &m_vertexbuffer);
        glDeleteBuffers(1, &m_elementarray);
    }

    void Renderer::Update()
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(m_program);
        glBindVertexArray(m_vertexarray);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementarray);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

} // namespace Photons
