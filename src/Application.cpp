#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Application.hpp"
#include "Renderer.hpp"
using namespace std;

Application::Application() {
    window = nullptr;
    isRunning = false;
    windowWidth = 640;
    windowHeight = 480;
}

bool Application::initialize() {
    if (!glfwInit()) {
        cout << "GLFW can't start" << endl;
        return false;
    }

    window = glfwCreateWindow(windowWidth, windowHeight, "Particle Simulation", NULL, NULL);

    if (!window) {
        cout << "Window creation failed" << endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);

    // gets the addresses of all openGL functions on this computer.
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    
    renderer.initialize();
    return true;
}

void Application::run() {
    isRunning = true;
    while (isRunning && !glfwWindowShouldClose(window)) {

        glfwPollEvents();

        // update()

        renderer.render();

        glfwSwapBuffers(window);
    }
}

void Application::shutdown() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::setWindowSize(int width, int height) {
    windowWidth = width;
    windowHeight = height;
}