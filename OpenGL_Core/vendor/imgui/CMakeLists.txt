cmake_minimum_required(VERSION 3.15)
project(imgui_glfw_opengl3)

add_library(imgui_glfw_opengl3 STATIC)

target_include_directories(imgui_glfw_opengl3 PUBLIC include)
target_include_directories(imgui_glfw_opengl3 PUBLIC ../glfw/include)

file(GLOB imgui_sources src/*.cpp)

target_sources(imgui_glfw_opengl3 PRIVATE ${imgui_sources})


