#include <iostream>
#include <assert.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define WIDTH  800
#define HEIGHT 600
#define TITLE  "Photons"

const char *vertex_shader_source = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;

    void main()
    {
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    }
)";

const char *fragment_shader_source = R"(
    #version 330 core
    out vec4 FragColor;

    void main()
    {
        FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    } 
)";

const char *vertex_shader_source2 = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;

    void main()
    {
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    }
)";

const char *fragment_shader_source2 = R"(
    #version 330 core
    out vec4 FragColor;

    void main()
    {
        FragColor = vec4(0.5f, 0.5f, 0.2f, 1.0f);
    } 
)";

GLFWwindow *g_window;

GLuint g_program;
GLuint g_program2;

GLuint vertex_shader, fragment_shader;

GLuint g_VAO;
GLuint g_VAO2;
GLuint g_VBO;
GLuint g_VBO2;
GLuint g_EBO;

void framebuffer_callback(GLFWwindow *window, int width, int height);
void input_callback(GLFWwindow *window);

GLuint create_shader(GLenum type, const char *source);
GLuint create_program();

int main()
{
    if (!glfwInit()) {
        std::cerr << "Can't initialize GLFW\n";
        return 1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    g_window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
    assert(g_window != nullptr);
    glfwMakeContextCurrent(g_window);
    glfwSetFramebufferSizeCallback(g_window, framebuffer_callback);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cerr << "Can't initialize Glad\n";
        return 1;
    }

    vertex_shader = create_shader(GL_VERTEX_SHADER, vertex_shader_source);
    if (!vertex_shader) {
        std::cerr << "Vertex Error\n";
        return 1;
    }

    fragment_shader = create_shader(GL_FRAGMENT_SHADER, fragment_shader_source);
    if (!vertex_shader) {
        std::cerr << "Fragment Error\n";
        return 1;
    }

    g_program = create_program();
    if (!vertex_shader) {
        std::cerr << "Program Error\n";
        return 1;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    vertex_shader = create_shader(GL_VERTEX_SHADER, vertex_shader_source2);
    if (!vertex_shader) {
        std::cerr << "Vertex Error\n";
        return 1;
    }

    fragment_shader =
        create_shader(GL_FRAGMENT_SHADER, fragment_shader_source2);
    if (!vertex_shader) {
        std::cerr << "Fragment Error\n";
        return 1;
    }

    g_program2 = create_program();
    if (!vertex_shader) {
        std::cerr << "Program Error\n";
        return 1;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    glGenVertexArrays(1, &g_VAO);
    glGenVertexArrays(1, &g_VAO2);
    glGenBuffers(1, &g_VBO);
    glGenBuffers(1, &g_VBO2);
    glGenBuffers(1, &g_EBO);

    float vertices[] = {
        0.1f, -0.5f, 0.0f, // Left
        0.9f, -0.5f, 0.0f, // Right
        0.5f, 0.5f,  0.0f, // Top
    };

    float vertices2[] = {
        -0.1f, -0.5f, 0.0f, // Left 2
        -0.9f, -0.5f, 0.0f, // Right 2
        -0.5f, 0.5f,  0.0f  // Top 2
    };

    // unsigned int indices[] = {
    //     0, 1, 3, // First Set
    //     1, 2, 3  // Second Set
    // };

    glBindVertexArray(g_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, g_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
    //              GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    glBindVertexArray(g_VAO2);

    glBindBuffer(GL_ARRAY_BUFFER, g_VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    while (!glfwWindowShouldClose(g_window)) {
        input_callback(g_window);

        glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(g_program);

        glBindVertexArray(g_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(g_program2);

        glBindVertexArray(g_VAO2);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(g_window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &g_VAO);
    glDeleteBuffers(1, &g_VBO);
    glDeleteBuffers(1, &g_EBO);
    glDeleteProgram(g_program);

    glfwTerminate();
    return 0;
}

inline void framebuffer_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void input_callback(GLFWwindow *window)
{
    if (glfwGetKey(g_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(g_window, true);

    if (glfwGetKey(g_window, GLFW_KEY_W) == GLFW_PRESS) {
        GLint mode[2];
        glGetIntegerv(GL_POLYGON_MODE, mode);

        if (mode[0] == GL_FILL) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glfwWaitEventsTimeout(0.5);
        } else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glfwWaitEventsTimeout(0.5);
        };
    }
}

GLuint create_shader(GLenum type, const char *source)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    int  success;
    char info[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 1024, NULL, info);
        std::cerr << "ERROR::SHADER::COMPILATION\n" << info << '\n';
        return 0;
    }

    return shader;
}

GLuint create_program()
{
    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    int  success;
    char info[1024];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 1024, NULL, info);
        std::cerr << "ERROR::PROGRAM::LINKING\n" << info << '\n';
        return 0;
    }

    return program;
}
