#include "Application.hpp"
#include <iostream>
#include <GLFW/glfw3.h>
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
    return true;
}

void Application::run() {
    isRunning = true;
    while (isRunning && !glfwWindowShouldClose(window)) {

        glfwPollEvents();

        //update()

        //render();

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