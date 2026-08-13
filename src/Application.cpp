#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Application.hpp"
#include "Renderer.hpp"
#include <cuda_runtime.h>
#include <cuda_gl_interop.h>
using namespace std;

// default constructor
Application::Application() {
    window = nullptr;
    isRunning = false;
    windowWidth = 640;
    windowHeight = 480;
}

// initilize application function
bool Application::initialize() {
    // start glfw
    if (!glfwInit()) {
        cout << "GLFW can't start" << endl;
        return false;
    }

    // create a glfw window
    window = glfwCreateWindow(windowWidth, windowHeight, "Particle Simulation", NULL, NULL);

    // if it doesn't work then terminate glfw and return false
    if (!window) {
        cout << "Window creation failed" << endl;
        glfwTerminate();
        return false;
    }

    // specify this window for the calling thread for opengl
    glfwMakeContextCurrent(window);

    // gets the addresses of all openGL functions on this computer.
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    cudaError_t error = cudaGLSetGLDevice(0);

    if (error != cudaSuccess) {
        cout << "cudaGLSetGLDevice failed: "
            << cudaGetErrorString(error) << endl;
        return false;
    }

    const size_t particleCount = 1000;

    // Initialize particle system with 1000 particles
    if (!particleSystem.initialize(particleCount)) {
        cerr << "Failed to initialize particle system.\n";
        return false;
    }

    // Initialize renderer with the same count
    if (!renderer.initialize(particleSystem.getParticleCount())) {
        cerr << "Failed to initialize renderer.\n";
        return false;
    }

    float3* positions = renderer.beginParticleUpdate();
    if (positions == nullptr) {
        cerr << "Failed to map particle VBO.\n";
        return false;
    }
    particleSystem.initializePositions(positions);

    renderer.endParticleUpdate();

    return true;
}

// function that runs the application
void Application::run() {

    // application is running and keep running until the window closes
    isRunning = true;

    // get previous time so that we can tell how much time passes between each frame
    float previousTime = glfwGetTime();

    while (isRunning && !glfwWindowShouldClose(window)) {

        // calculate the change in time between frames by getting current time and subtracting to prev
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - previousTime;
        previousTime = currentTime;


        // poll events (keyboard inputs, changing window size, and more)
        glfwPollEvents();

        // create the positions pointer for the renderer
        float3* positions = renderer.beginParticleUpdate();

        if (positions == nullptr) {
            cerr << "Could not get particle positions\n";
            break;
        }

        // update the particle system
        particleSystem.update(positions, deltaTime);

        // updated particle can be used by opengl now
        renderer.endParticleUpdate();

        // render the system
        renderer.render(particleSystem.getParticleCount());

        /* swaps buffers front buffer is current image on screen
            back buffer is the image drawn during rendering 
            in other words keep updating the image */
        glfwSwapBuffers(window);
    }
}
// function for shutting down the application
void Application::shutdown() {

    // shutdown the particle system
    particleSystem.shutdown();

    // shutdown the renderer
    renderer.shutdown();

    // destroy window
    glfwDestroyWindow(window);

    // terminate glfw
    glfwTerminate();

    // shutting down window so make window null and isRunning false.
    window = nullptr;
    isRunning = false;
}

// function setting the window size.
void Application::setWindowSize(int width, int height) {
    windowWidth = width;
    windowHeight = height;
}