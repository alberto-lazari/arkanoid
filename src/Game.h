#pragma once

#include <memory>

struct GLFWwindow;
class Level;

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
    void webMainLoop();

private:
    GLFWwindow* window;

    float lastTime = 0.0f;

    std::unique_ptr<Level> level;

    bool isPressed(int key) const;

    void init();
    void processInput();
    void render(float alpha);
    void update(float dt);
};
