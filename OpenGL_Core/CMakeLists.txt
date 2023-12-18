cmake_minimum_required(VERSION 3.20)
project(OpenGL_Core)

add_library(OpenGL_Core STATIC)
target_compile_features(OpenGL_Core PRIVATE cxx_std_20)

# Vendors
option(SPDLOG_USE_STD_FORMAT ON)
target_compile_definitions(OpenGL_Core PUBLIC _SECURE_SCL=FALSE)

add_subdirectory(vendor/glad)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/imgui-docking)
add_subdirectory(vendor/glm)
add_subdirectory(vendor/spdlog)

# Core
target_include_directories(OpenGL_Core PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

file(GLOB_RECURSE core_sources CONFIGURE_DEPENDS src/*.cpp)
target_sources(OpenGL_Core PRIVATE ${core_sources})

target_precompile_headers(OpenGL_Core PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/pch.hpp")

# Linking all libraries
target_link_libraries(OpenGL_Core PUBLIC glad glfw glm imgui spdlog
)

# OS Specific MACROs

if(WIN32)
    target_compile_definitions(OpenGL_Core PUBLIC WIN32)
elseif (APPLE)
    target_compile_definitions(OpenGL_Core PUBLIC APPLE)
elseif(UNIX AND NOT APPLE)
    target_compile_definitions(OpenGL_Core PUBLIC LINUX)
endif()

# MSVC Configurations

if(MSVC) # For Visual Studio
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release") # limits the CONFIGURATION_TYPES to Debug and Release
    set(CMAKE_CXX_FLAGS_RELEASE "-DRELEASE /MT") #if compiled using --config Release , RELEASE will be defined and compiled using /MT
    set(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG /MTd") #if compiled using --config Debug, DEBUG macro will be defined and compiled using /MTd
else() # BUILD_TYPE is specified on BUILD TIME unlike visual studio (NEEDS TO BE TESTED USING OTHER COMPILERS LATER)
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release") # limits the CONFIGURATION_TYPES to Debug and Release
    set(CMAKE_CXX_FLAGS_RELEASE "-DRELEASE") #if compiled using --config Release , RELEASE will be defined and compiled using /MT
    set(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG") #if compiled using --config Debug, DEBUG macro will be defined and compiled using /MTd
endif()