cmake_minimum_required(VERSION 3.16)
project(Arkanoid)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Executable
file(GLOB SRC_FILES src/*.cpp)
add_executable(Arkanoid ${SRC_FILES})
target_include_directories(Arkanoid PRIVATE include external/glad/include)

# glad
add_library(glad external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

# GLFW
if (EMSCRIPTEN)
    target_link_options(Arkanoid PRIVATE
        "-sUSE_GLFW=3"
        "-sFULL_ES3=1"
        "-sWASM=1"
        "-sALLOW_MEMORY_GROWTH=1"
    )
    target_link_libraries(Arkanoid PRIVATE glad)
else()
    # Add GLFW system dependency
    add_subdirectory(external/glfw)
    target_link_libraries(Arkanoid PRIVATE glfw glad)
endif()

# Add warnings
if (MSVC)
    target_compile_options(Arkanoid PRIVATE /W4 /permissive-)
else()
    target_compile_options(Arkanoid PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Build universal binary on macOS
set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64" CACHE STRING "Build architectures for macOS" FORCE)
