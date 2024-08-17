cmake_minimum_required(VERSION 3.8)
project(pbl)

add_subdirectory(src)

add_executable("${PROJECT_NAME}" src/main.cpp src/glad.c)

target_link_libraries("${PROJECT_NAME}" PUBLIC glfw Lib)