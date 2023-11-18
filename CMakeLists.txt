# Martin Minarik, MIN0139, 2023

cmake_minimum_required(VERSION 3.25)
project(zpg_min0139)

set(CMAKE_CXX_STANDARD 17)

# Set paths
set(RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources)

# Find scripts
find_package(OpenGL REQUIRED)
find_library(SOIL_LIBRARY NAMES soil)
find_package(assimp REQUIRED)
find_package(GLM REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
unset(SOIL_INCLUDE_DIRS CACHE)
find_path(
        SOIL_INCLUDE_DIRS
        NAMES "SOIL.h"
        PATH_SUFFIXES  "SOIL"
)


# Project HEADERS + SOURCES
include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

# Add exe
add_executable(${PROJECT_NAME} ${SOURCES})

# Libs - include headers
target_include_directories(${PROJECT_NAME} PRIVATE ${SOIL_INCLUDE_DIRS})

# Libs - link
target_link_libraries(${PROJECT_NAME} ${ASSIMP_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${SOIL_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY})
target_link_libraries(${PROJECT_NAME} GLEW::GLEW)
target_link_libraries(${PROJECT_NAME} glfw)

# Copy resources
file(COPY ${RESOURCES_DIR} DESTINATION ${CMAKE_BINARY_DIR})
