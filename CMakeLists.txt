cmake_minimum_required(VERSION 3.10)
project(Breakout)

set(CMAKE_CXX_STANDARD 17)

# 1. Include Directories
# ----------------------
# Look for headers in 'include' (glad, glfw, glm)
include_directories(${CMAKE_SOURCE_DIR}/include)
# Look for headers in 'Game' (game.h, shader.h, etc.)
include_directories(${CMAKE_SOURCE_DIR}/Game)

# 2. Link Directories (Libraries)
# ----------------------
link_directories(${CMAKE_SOURCE_DIR}/lib)

# 3. Source Files
# ----------------------
# We list all the cpp files inside the Game folder
set(GAME_SOURCES
    Game/program.cpp
    Game/game.cpp
    Game/resource_manager.cpp
    Game/shader.cpp
    Game/texture.cpp
    Game/sprite_renderer.cpp
    Game/game_object.cpp   # <--- ADD
    Game/game_level.cpp
)

# Check if stb_image.cpp is in Game or Root. 
# If you moved it to Game, remove "stb_image.cpp" from below and add "Game/stb_image.cpp" above.
# Assuming glad.c and stb_image.cpp are still in the root Graphics folder:
set(LIB_SOURCES
    glad.c
    stb_image.cpp
)

# 4. Create Executable
# ----------------------
add_executable(Breakout ${GAME_SOURCES} ${LIB_SOURCES})

# 5. Link Libraries
# ----------------------
target_link_libraries(Breakout glfw3 opengl32 gdi32 user32)