#include "Game.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>

#include "Paddle.h"

Game::Game(int width, int height, const char* title)
    : window(nullptr)
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
}

Game::~Game()
{
    glfwTerminate();
}

int Game::run()
{
    if (!window) return EXIT_FAILURE;

    init();

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

void Game::init()
{
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow*, int width, int height) {
        glViewport(0, 0, width, height);
    });

    // Use V-Sync
    glfwSwapInterval(1);

    // Set clear color
    glClearColor(0.15f, 0.15f, 0.15f, 1.0f);

    paddle = new Paddle;
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

    int width;
    int height;
    glfwGetFramebufferSize(window, &width, &height);
    paddle->render(static_cast<float>(width) / height);
}
