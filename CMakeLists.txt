cmake_minimum_required(VERSION 3.20)
project(PROJECT)

# Pre-Settings
if(MSVC) 
    # Executables and Library Locations
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>/lib)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>/bin)
elseif(DEFINED CMAKE_BUILD_TYPE)
    if( NOT (${CMAKE_BUILD_TYPE} STREQUAL "Debug" OR ${CMAKE_BUILD_TYPE} STREQUAL "Release" ) )  
        set(${CMAKE_BUILD_TYPE} "Release")
    endif()
    
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/bin)
else()
    message(FATAL_ERROR "Error: CMAKE_BUILD_TYPE must be specified")
endif()

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


set(ASSETS_DEBUG_PATH "${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/assets/")
set(ASSETS_RELEASE_PATH "assets/")
# Multi Config Generators
if(MSVC)
    # Unified ASSETS_PATH and build type definitions
    # Macros
    target_compile_definitions(project_compiler_flags INTERFACE 
        $<$<CONFIG:Debug>:DEBUG;ASSETS_PATH="${ASSETS_DEBUG_PATH}"/>
        $<$<CONFIG:Release>:RELEASE;ASSETS_PATH="${ASSETS_RELEASE_PATH}">
    )
    # Post Commands
    add_custom_command(
        TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/assets
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets
    )
elseif(DEFINED CMAKE_BUILD_TYPE)
    if( NOT (${CMAKE_BUILD_TYPE} STREQUAL "Debug" OR ${CMAKE_BUILD_TYPE} STREQUAL "Release" ) )  
        set(${CMAKE_BUILD_TYPE} "Release")
    endif()

    if( ${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        # MACRO
        target_compile_definitions(project_compiler_flags INTERFACE
            DEBUG;ASSETS_PATH="${ASSETS_DEBUG_PATH}"
        )
    else()
        # MACRO
        target_compile_definitions(project_compiler_flags INTERFACE
            DEBUG;ASSETS_PATH="${ASSETS_RELEASE_PATH}"
        )
    endif()

    # Compiler Flags
    add_custom_command(
    TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/assets
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets
    )
else()
    message(FATAL_ERROR "Error: CMAKE_BUILD_TYPE must be specified")
endif()

# Vendor
add_subdirectory(OpenGL_Core)

# Linking Libraries
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE project_compiler_flags OpenGL_Core)