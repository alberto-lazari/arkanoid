#pragma once

#include "Quad.h"
#include "Paddle.h"
#include "Ball.h"
#include "BrickMap.h"

#include <vector>

class Level
{
public:
    Level(std::vector<Brick>&& bricks, unsigned int lives = 1);
    virtual ~Level() = default;

    constexpr int getLives() const { return lives; }

    void render(float aspectRatio, float alpha);
    void update(float dt);

    void movePaddle(float dx);
    void start();
    bool gameOver() const;

private:
    Quad background;
    Paddle paddle;
    Ball ball;
    BrickMap brickMap;

    int lives;

    virtual std::vector<Brick> makeBrickMap() const = 0;
    virtual float getBallSpeed() const = 0;
};
