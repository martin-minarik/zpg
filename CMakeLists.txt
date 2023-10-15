# Martin Minarik, MIN0139, 2023

cmake_minimum_required(VERSION 3.25)
project(zpg_min0139)

set(CMAKE_CXX_STANDARD 17)

# Set aliases for paths
set(ZPG_LIBS ${CMAKE_CURRENT_SOURCE_DIR}/../libs)
set(GLFW_DIR ${ZPG_LIBS}/glfw-3.3.8.bin.WIN64)
set(GLEW_DIR ${ZPG_LIBS}/glew-2.1.0)
set(GLM_DIR ${ZPG_LIBS}/glm-0.9.9.8)

# Find and setup OpenGL for project
find_package(OpenGL REQUIRED)

# Set the include directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# Get the list of source files
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

# Include external headers GLFW, GLEW, GLM
target_include_directories(${PROJECT_NAME} PRIVATE ${GLFW_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${GLEW_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${GLM_DIR}/glm)

# Link external GLFW, GLEW a OPENGL
target_link_libraries(${PROJECT_NAME} PRIVATE ${GLFW_DIR}/lib-mingw-w64/glfw3.dll)
target_link_libraries(${PROJECT_NAME} PRIVATE ${GLEW_DIR}/bin/Release/x64/glew32.dll)
target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_gl_LIBRARY})

# Copy glfw3.dll to cmake-build folder
file(COPY ${GLFW_DIR}/lib-mingw-w64/glfw3.dll DESTINATION ${CMAKE_BINARY_DIR})
# Copy glfw3.dll to cmake-build folder
file(COPY ${GLEW_DIR}/bin/Release/x64/glew32.dll DESTINATION ${CMAKE_BINARY_DIR})
