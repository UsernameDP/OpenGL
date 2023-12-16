cmake_minimum_required(VERSION 3.15)
project(OpenGL_Core)

add_library(OpenGL_Core STATIC)
add_library(OpenGL_Core_compiler_flags INTERFACE)
target_compile_features(OpenGL_Core_compiler_flags INTERFACE cxx_std_11)


# Vendors
add_subdirectory(vendor/glad)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/imgui)
add_subdirectory(vendor/glm)
add_subdirectory(vendor/spdlog)

target_link_libraries(OpenGL_Core opengl32 glfw imgui_glfw_opengl3 spdlogd)

# Core
target_include_directories(OpenGL_Core PUBLIC src)

file(GLOB_RECURSE core_sources CONFIGURE_DEPENDS src/*.cpp)
message("OpenGL_Core sources: ${core_sources}")
target_sources(OpenGL_Core PRIVATE ${core_sources})
