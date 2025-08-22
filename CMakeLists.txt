cmake_minimum_required(VERSION 3.16)
project(Arkanoid)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add dependencies
add_subdirectory(external/glfw)

add_library(glad external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

# Executable
file(GLOB SRC_FILES src/*.cpp)
add_executable(Arkanoid ${SRC_FILES})

target_include_directories(Arkanoid PRIVATE include external/glad/include)
target_link_libraries(Arkanoid PRIVATE glfw glad)
