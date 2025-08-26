#include "Game.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <algorithm>
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
    float previousTime = glfwGetTime();
    float accumulator = 0.0;
    while (!glfwWindowShouldClose(window))
    {
        const float currentTime = glfwGetTime();
        // Cap deltatime to avoid freeze
        const float dt = std::min(currentTime - previousTime, MAX_FRAME_TIME);
        accumulator += dt;
        previousTime = currentTime;

        processInput();
        while (accumulator > FIXED_STEP)
        {
            update(FIXED_STEP);
            accumulator -= FIXED_STEP;
        }
        render(accumulator / FIXED_STEP);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return EXIT_SUCCESS;
}

bool Game::isPressed(int key)
{
    return glfwGetKey(window, key) == GLFW_PRESS;
}

void Game::init()
{
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow*, int width, int height) {
        glViewport(0, 0, width, height);
    });

    // Do not use V-Sync (since it causes frame jitter that I couldn't fix as of now)
    glfwSwapInterval(0);

    // Set clear color
    glClearColor(0.15f, 0.15f, 0.15f, 1.0f);

    paddle = std::make_unique<Paddle>();
}

void Game::processInput()
{
    if (isPressed(GLFW_KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void Game::render(float alpha)
{
    // Clear color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    int width;
    int height;
    glfwGetFramebufferSize(window, &width, &height);
    paddle->render(static_cast<float>(width) / height, alpha);
}

void Game::update(float dt)
{
    if (isPressed(GLFW_KEY_LEFT)) paddle->move(-dt);
    else if (isPressed(GLFW_KEY_RIGHT)) paddle->move(dt);

    paddle->update(dt);
}
