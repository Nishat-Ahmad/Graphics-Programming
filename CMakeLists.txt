cmake_minimum_required(VERSION 3.10)
project(Graphics)

# 1. Use modern C++
set(CMAKE_CXX_STANDARD 17)

# 2. Include directories (for headers)
include_directories(${CMAKE_SOURCE_DIR}/include)

# 3. Link directories (for .a libraries)
link_directories(${CMAKE_SOURCE_DIR}/lib)

# TARGET 1: HelloWindow
# add_executable(HelloWindow hellowindow.cpp glad.c)
# target_link_libraries(HelloWindow glfw3 opengl32 gdi32 user32)

# TARGET 2: HelloTriangle
# add_executable(HelloTriangle helloTriangle.cpp glad.c)
# target_link_libraries(HelloTriangle glfw3 opengl32 gdi32 user32)

# Create Executable
add_executable(HelloShader helloShader.cpp glad.c)
target_link_libraries(HelloShader glfw3 opengl32 gdi32 user32)