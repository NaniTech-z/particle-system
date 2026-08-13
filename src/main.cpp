#include <GLFW/glfw3.h>
#include <iostream>
#include "Application.hpp"
using namespace std;

int main() {
    // create the application
    Application app;
    int width, height;
    
    // input for initial window resolution
    cout << "Input width of window: ";
    cin >> width;
    cout << "Input height of window: ";
    cin >> height;
    
    // set the resolution
    app.setWindowSize(width, height);
    
    // try to initialize the app if it doesn't work return -1
    if(!app.initialize())
        return -1;

    // run the app
    app.run();

    // shutdown app
    app.shutdown();

    return 0;
}