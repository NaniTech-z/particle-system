#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Renderer.hpp"
using namespace std;

// creates shaders, VAO (vertex array object), VBO (vertex buffer object)
bool Renderer::initialize() {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    //create shaders later

    return true;
}

void Renderer::render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Renderer::shutdown() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(shaderProgram);
}