#pragma once
#include <GLFW/glfw3.h>
using namespace std;

struct cudaGraphicsResource;

class Renderer {
    public:
        bool initialize(size_t particleCount);
        void render(size_t particleCount);
        void shutdown();
        float3* beginParticleUpdate();
        void endParticleUpdate();
    
    private:
        GLuint vao = 0; // vertex array object
        GLuint vbo = 0; // vertex buffer object
        GLuint shaderProgram = 0;

        cudaGraphicsResource* cudaVBO = nullptr;
};