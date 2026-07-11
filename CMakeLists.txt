cmake_minimum_required(VERSION 3.28)

project(particle_system VERSION 1.0.0 LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CUDA_STANDARD 17)

find_package(glfw3 CONFIG REQUIRED)

add_executable(main 
    src/main.cpp
    src/Application.cpp
)

target_include_directories(main PRIVATE
    include
)

target_link_libraries(main PRIVATE glfw)