cmake_minimum_required(VERSION 3.20)
project(PROJECT)

# Executables and Library Locations
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BINARY_DIR}/Debug/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BINARY_DIR}/Debug/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BINARY_DIR}/Debug/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BINARY_DIR}/Release/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BINARY_DIR}/Release/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BINARY_DIR}/Release/bin)

# PROJECT Files
add_executable(${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_NAME}/src/main.cpp)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_PROJECT_NAME}/include)
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS ${CMAKE_PROJECT_NAME}/src/*.cpp)
target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})

# Compiler flags interface library
add_library(project_compiler_flags INTERFACE)
target_compile_features(project_compiler_flags INTERFACE cxx_std_23)

# OS Specific MACROs
if(WIN32)
    target_compile_definitions(project_compiler_flags INTERFACE WIN32)
elseif(APPLE)
    target_compile_definitions(project_compiler_flags INTERFACE APPLE)
elseif(UNIX AND NOT APPLE)
    target_compile_definitions(project_compiler_flags INTERFACE LINUX)
endif()

# Unified ASSETS_PATH and build type definitions
set(ASSETS_DEBUG_PATH "${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/assets/")
set(ASSETS_RELEASE_PATH "assets/")
target_compile_definitions(project_compiler_flags INTERFACE 
    $<$<CONFIG:Debug>:DEBUG;ASSETS_PATH="${ASSETS_DEBUG_PATH}">
    $<$<CONFIG:Release>:RELEASE;ASSETS_PATH="${ASSETS_RELEASE_PATH}">
)

# Vendor
add_subdirectory(OpenGL_Core)

# Linking Libraries
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE project_compiler_flags OpenGL_Core)

# Post Commands
add_custom_command(
    TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/assets
        $<$<CONFIG:Debug>:${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/assets>$<$<CONFIG:Release>:${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/assets>
)
