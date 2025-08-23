#pragma once

class GLFWwindow;
class Paddle;

class Game
{
public:
    Game(int framebufferWidth, int framebufferHeight, const char* title);
    ~Game();

    int run();

private:
    GLFWwindow* window;

    Paddle* paddle;

    void init();
    void processInput();
    void render();
};
