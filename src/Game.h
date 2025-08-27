#pragma once

#include <memory>

struct GLFWwindow;
class Quad;
class Paddle;
class Ball;
class BrickMap;

class Game
{
public:
    static constexpr float FIXED_STEP = 1.0 / 60.0;
    static constexpr float MAX_FRAME_TIME = 0.25;

    static constexpr float WIDTH = 4.0f;
    static constexpr float HEIGHT = 3.0f;

    Game(const char* title);
    ~Game();

    int run();

private:
    GLFWwindow* window;

    std::unique_ptr<Quad> background;
    std::unique_ptr<Paddle> paddle;
    std::unique_ptr<Ball> ball;
    std::unique_ptr<BrickMap> brickMap;

    bool isPressed(int key) const;

    void init();
    void processInput();
    void render(float alpha);
    void update(float dt);
};
