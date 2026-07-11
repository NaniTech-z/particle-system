#include <GLFW/glfw3.h>
#include <iostream>
#include "Application.hpp"
using namespace std;

int main() {
    Application app;
    int width, height;
    cout << "Input width of window: ";
    cin >> width;
    cout << "Input height of window: ";
    cin >> height;
    app.setWindowSize(width, height);

    if(!app.initialize())
        return -1;

    app.run();

    app.shutdown();

    return 0;
}