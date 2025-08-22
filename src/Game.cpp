#include "Game.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>

Game::Game(int width, int height, const char* title)
    : window(nullptr)
    , width(width)
    , height(height)
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return;
    }

    // Set GLFW for OpenGL 3.3 Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create Window and OpenGL context
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create window\n";
        return;
    }
    glfwMakeContextCurrent(window);

    // Load modern OpenGL functions
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD\n";
        window = nullptr;
        return;
    }

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow*, int width, int height) {
        glViewport(0, 0, width, height);
    });

    // Use V-Sync
    glfwSwapInterval(1);

    // Set clear color
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
}

Game::~Game()
{
    glfwTerminate();
}

void Game::processInput()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void Game::render()
{
    // Clear color buffer
    glClear(GL_COLOR_BUFFER_BIT);
}

int Game::run()
{
    if (!window) return EXIT_FAILURE;

    // Window main loop
    while (!glfwWindowShouldClose(window))
    {
        processInput();
        render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return EXIT_SUCCESS;
}
