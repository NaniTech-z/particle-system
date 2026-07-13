#pragma once
#include <GLFW/glfw3.h>
using namespace std;

class Renderer {
    public:
        bool initialize();
        void render();
        void shutdown();
    
    private:
        GLuint vao = 0;
        GLuint vbo = 0;
        GLuint shaderProgram = 0;
};