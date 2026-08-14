#include "Timer.hpp"
#include <GLFW/glfw3.h>

Timer::Timer() {
    previousTime = static_cast<float>(glfwGetTime());
    deltaTime = 0.0f;
    elapsedTime = 0.0f;
}

void Timer::update() {
    float currentTime = static_cast<float>(glfwGetTime());
    deltaTime = currentTime - previousTime;
    previousTime = currentTime;
    elapsedTime += deltaTime;
}

float Timer::getDeltaTime() const {
    return deltaTime;
}

float Timer::getElapsedTime() const {
    return elapsedTime;
}




