#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using namespace std;

struct cudaGraphicsResource;

class Renderer {
    public:
        bool initialize(size_t particleCount);
        void render(size_t particleCount, const glm::mat4& view, const glm::mat4& projection);
        void shutdown();
        float3* beginParticleUpdate();
        void endParticleUpdate();
    
    private:
        GLuint vao = 0; // vertex array object
        GLuint vbo = 0; // vertex buffer object
        GLuint shaderProgram = 0;
        GLuint viewLocation;
        GLuint projectionLocation;
        cudaGraphicsResource* cudaVBO = nullptr;
};