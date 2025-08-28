#include "Game.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <algorithm>
#include <cstdlib>
#include <iostream>

#include "DemoLevel.h"

Game::Game(const char* title)
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
    window = glfwCreateWindow(1024, 768, title, nullptr, nullptr);
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
    lastTime = glfwGetTime();
    double accumulator = 0.0;
    while (!glfwWindowShouldClose(window))
    {
        const double currentTime = glfwGetTime();
        // Cap deltatime to avoid freeze
        const double dt = std::min(currentTime - lastTime, MAX_FRAME_TIME);
        accumulator += dt;
        lastTime = currentTime;

        processInput();
        while (accumulator > FIXED_STEP)
        {
            update(static_cast<float>(FIXED_STEP));
            accumulator -= FIXED_STEP;
        }
        render(static_cast<float>(accumulator / FIXED_STEP));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return EXIT_SUCCESS;
}


void Game::webMainLoop()
{
    const double currentTime = glfwGetTime();
    // Cap deltatime to avoid freeze
    const double dt = std::min(currentTime - lastTime, MAX_FRAME_TIME);
    lastTime = currentTime;

    processInput();
    update(static_cast<float>(dt));
    render(1.0f);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

bool Game::isPressed(int key) const
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
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    level = std::make_unique<DemoLevel>();
}

void Game::processInput()
{
    // ESC/Q to quit
    if (isPressed(GLFW_KEY_ESCAPE) || isPressed(GLFW_KEY_Q))
        glfwSetWindowShouldClose(window, true);

    // Space to launch ball and start game
    if (isPressed(GLFW_KEY_SPACE)) level->start();
}

void Game::render(float alpha)
{
    // Clear color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    int width;
    int height;
    glfwGetFramebufferSize(window, &width, &height);
    const float aspectRatio = static_cast<float>(width) / height;

    level->render(aspectRatio, alpha);
}

void Game::update(float dt)
{
    if (isPressed(GLFW_KEY_LEFT)) level->movePaddle(-dt);
    else if (isPressed(GLFW_KEY_RIGHT)) level->movePaddle(dt);

    level->update(dt);

    if (level->gameOver())
    {
        level.reset();
        level = std::make_unique<DemoLevel>();
        level->update(dt);
    }
}
