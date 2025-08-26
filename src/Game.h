#pragma once

#include <memory>

class GLFWwindow;
class Paddle;
class Ball;

class Game
{
public:
    static constexpr float FIXED_STEP = 1.0 / 60.0;
    static constexpr float MAX_FRAME_TIME = 0.25;

    Game(int framebufferWidth, int framebufferHeight, const char* title);
    ~Game();

    int run();

private:
    GLFWwindow* window;

    std::unique_ptr<Paddle> paddle;
    std::unique_ptr<Ball> ball;

    bool isPressed(int key);

    void init();
    void processInput();
    void render(float alpha);
    void update(float dt);
};
