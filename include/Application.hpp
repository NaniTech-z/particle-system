#pragma once
#include <GLFW/glfw3.h>
#include "ParticleSystem.hpp"
#include "Renderer.hpp"
using namespace std;

class Application {
    public:
        Application();

        bool initialize();
        void run();
        void shutdown();

        void setWindowSize(int width, int height);

    private:
        GLFWwindow* window = nullptr;
        Renderer renderer;
        ParticleSystem particleSystem;
        float previousTime = 0.0f;
        bool isRunning;
        int windowWidth;
        int windowHeight;
};