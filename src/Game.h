#pragma once

class GLFWwindow;

class Game
{
public:
    Game(int width, int height, const char* title);
    ~Game();

    int run();

private:
    GLFWwindow* window;
    int width, height;

    void processInput();
    void render();
};
