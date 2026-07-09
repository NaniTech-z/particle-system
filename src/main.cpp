#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

int main() {

    if (!glfwInit()) {
        cout << "GLFW can't start" << endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "Simulation", NULL, NULL);

    if (!window) {
        cout << "Window creation failed" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {

        glfwPollEvents();

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}