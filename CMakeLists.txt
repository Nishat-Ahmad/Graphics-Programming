cmake_minimum_required(VERSION 3.10)
project(Breakout)

set(CMAKE_CXX_STANDARD 17)

# 1. Include Directories
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/Game)

# 2. Link Directories
link_directories(${CMAKE_SOURCE_DIR}/lib)

# 3. Source Files
set(GAME_SOURCES
    Game/program.cpp
    Game/game.cpp
    Game/resource_manager.cpp
    Game/shader.cpp
    Game/texture.cpp
    Game/sprite_renderer.cpp
    Game/game_object.cpp
    Game/ball_object.cpp
    Game/game_level.cpp
)

set(LIB_SOURCES
    glad.c
    stb_image.cpp
)

# 4. Create Executable
add_executable(Breakout ${GAME_SOURCES} ${LIB_SOURCES})

# 5. Link Libraries
target_link_libraries(Breakout glfw3 opengl32 gdi32 user32)