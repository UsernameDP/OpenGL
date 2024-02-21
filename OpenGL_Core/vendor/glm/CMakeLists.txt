cmake_minimum_required(VERSION 3.15)
project(glm)

add_library(glm INTERFACE) # Since it is a header library no sources, hence an INTERFACE not STATIC

target_include_directories(glm INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
