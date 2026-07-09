cmake_minimum_required(VERSION 3.10)

project(particle_system VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 CONFIG REQUIRED)

add_executable(main 
    src/main.cpp
)

target_link_libraries(main PRIVATE glfw)