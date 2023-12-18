cmake_minimum_required(VERSION 3.20)

# -----------------------------------------------
# Change "PROJECT" below to the main of the directory
project(PROJECT)
# -----------------------------------------------

# Project
add_executable(${CMAKE_PROJECT_NAME} "${CMAKE_PROJECT_NAME}/src/main.cpp")
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC "${CMAKE_PROJECT_NAME}/include")
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_PROJECT_NAME}/src/*.cpp")
target_sources(${CMAKE_PROJECT_NAME} PRIVATE "${PROJECT_SOURCES}")
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE OpenGL_Core)

# Project Properties
target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_20)

# Vendor
add_subdirectory(OpenGL_Core)


# Executables and Library Locations
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


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

# Project is a "Window App" not "Console App"
if(MSVC)
    if(WIN32)
        target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE
            "$<$<CONFIG:Release>:/SUBSYSTEM:WINDOWS>"
            "$<$<CONFIG:Release>:/ENTRY:mainCRTStartup>"
        )
    endif()

endif()