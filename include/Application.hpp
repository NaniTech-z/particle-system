#pragma once
#include <GLFW/glfw3.h>
#include "ParticleSystem.hpp"
#include "Renderer.hpp"
#include "Camera.hpp"
#include "Timer.hpp"
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
        Camera camera;
        double lastMouseX;
        double lastMouseY;
        bool firstMouse;
        Timer timer;
        bool isRunning;
        int windowWidth;
        int windowHeight;
};