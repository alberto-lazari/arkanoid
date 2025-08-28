#pragma once

#include <memory>

struct GLFWwindow;
class Level;

class Game
{
public:
    static constexpr double FIXED_STEP = 1.0 / 60.0;
    static constexpr double MAX_FRAME_TIME = 0.25;

    static constexpr float WIDTH = 4.0f;
    static constexpr float HEIGHT = 3.0f;

    Game(const char* title);
    ~Game();

    int run();
    void webMainLoop();

private:
    GLFWwindow* window;

    double lastTime = 0.0;

    std::unique_ptr<Level> level;

    bool isPressed(int key) const;

    void init();
    void processInput();
    void render(float alpha);
    void update(float dt);
};
