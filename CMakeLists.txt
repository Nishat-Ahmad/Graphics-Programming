cmake_minimum_required(VERSION 3.10)
project(HelloWindow)

# 1. Tell CMake we want to use modern C++
set(CMAKE_CXX_STANDARD 17)

# 2. Tell CMake where the header files (.h) are
include_directories(${CMAKE_SOURCE_DIR}/include)

# 3. Tell CMake where the library files (.a) are
link_directories(${CMAKE_SOURCE_DIR}/lib)

# 4. Define the executable
#    We tell it to build "HelloWindow" using main.cpp AND glad.c
add_executable(HelloWindow hellowindow.cpp glad.c)

# 5. Link the libraries
#    Connects GLFW and the Windows graphics API to your program
target_link_libraries(HelloWindow glfw3 opengl32 gdi32)