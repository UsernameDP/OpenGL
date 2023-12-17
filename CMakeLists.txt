cmake_minimum_required(VERSION 3.15)

# -----------------------------------------------
# Change "PROJECT" below to the main of the directory
project(PROJECT)
# -----------------------------------------------

# Executables and Library Locations
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Configuration Types
    
if(MSVC) # For Visual Studio
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release") # limits the CONFIGURATION_TYPES to Debug and Release
    set(CMAKE_CXX_FLAGS_RELEASE "-DRELEASE /MT") #if compiled using --config Release , RELEASE will be defined and compiled using /MT
    set(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG /MTd") #if compiled using --config Debug, DEBUG macro will be defined and compiled using /MTd
else() # BUILD_TYPE is specified on BUILD TIME unlike visual studio (NEEDS TO BE TESTED USING OTHER COMPILERS LATER)
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release") # limits the CONFIGURATION_TYPES to Debug and Release
    set(CMAKE_CXX_FLAGS_RELEASE "-DRELEASE") #if compiled using --config Release , RELEASE will be defined and compiled using /MT
    set(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG") #if compiled using --config Debug, DEBUG macro will be defined and compiled using /MTd
endif()
    



# Vendor
add_subdirectory(OpenGL_Core)

# Project
add_executable(${CMAKE_PROJECT_NAME} "${CMAKE_PROJECT_NAME}/src/main.cpp")

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC "${CMAKE_PROJECT_NAME}/include")
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_PROJECT_NAME}/src/*.cpp")
target_sources(${CMAKE_PROJECT_NAME} PRIVATE "${PROJECT_SOURCES}")

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE OpenGL_Core)