#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "Renderer.hpp"
using namespace std;

static std::string readShaderFile(const char* filePath)
{
    std::ifstream file(filePath);

    if (!file)
    {
        std::cout << "Failed to open shader: "
                  << filePath << std::endl;

        return "";
    }

    std::stringstream stream;
    stream << file.rdbuf();

    return stream.str();
}

static unsigned int compileShader(
    unsigned int shaderType,
    const char* source)
{
    unsigned int shader = glCreateShader(shaderType);

    glShaderSource(
        shader,
        1,
        &source,
        nullptr
    );

    glCompileShader(shader);

    int success;

    glGetShaderiv(
        shader,
        GL_COMPILE_STATUS,
        &success
    );

    if (!success)
    {
        char infoLog[512];

        glGetShaderInfoLog(
            shader,
            512,
            nullptr,
            infoLog
        );

        std::cout
            << "Shader compilation failed:\n"
            << infoLog
            << std::endl;

        glDeleteShader(shader);

        return 0;
    }

    return shader;
}

static unsigned int createShaderProgram()
{
    std::string vertexSource =
        readShaderFile("shaders/particle.vert");

    std::string fragmentSource =
        readShaderFile("shaders/particle.frag");

    if (vertexSource.empty() ||
        fragmentSource.empty())
    {
        return 0;
    }

    unsigned int vertexShader =
        compileShader(
            GL_VERTEX_SHADER,
            vertexSource.c_str()
        );

    unsigned int fragmentShader =
        compileShader(
            GL_FRAGMENT_SHADER,
            fragmentSource.c_str()
        );

    if (vertexShader == 0 ||
        fragmentShader == 0)
    {
        return 0;
    }

    unsigned int program =
        glCreateProgram();

    glAttachShader(
        program,
        vertexShader
    );

    glAttachShader(
        program,
        fragmentShader
    );

    glLinkProgram(program);

    int success;

    glGetProgramiv(
        program,
        GL_LINK_STATUS,
        &success
    );

    if (!success)
    {
        char infoLog[512];

        glGetProgramInfoLog(
            program,
            512,
            nullptr,
            infoLog
        );

        std::cout
            << "Shader program linking failed:\n"
            << infoLog
            << std::endl;

        glDeleteProgram(program);

        program = 0;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

// creates shaders, VAO (vertex array object), VBO (vertex buffer object)
bool Renderer::initialize() {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    // temporary particle at origin
    float particle[] = {
        0.0f, 0.0f, 0.0f
    };

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(particle),
        particle,
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3*sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(0);

    shaderProgram = createShaderProgram();
    if (shaderProgram == 0) {
        cout << "Failed to create shader program" << endl;

        return false;
    }

    glPointSize(10.0f);

    return true;
}

void Renderer::render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
    glDrawArrays(GL_POINTS, 0, 1);
}

void Renderer::shutdown() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(shaderProgram);
}