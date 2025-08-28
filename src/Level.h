#pragma once

#include "Quad.h"
#include "Paddle.h"
#include "Ball.h"
#include "BrickMap.h"

#include <vector>

class Level
{
public:
    Level(std::vector<Brick>&& bricks);

    void render(float aspectRatio, float alpha);
    void update(float dt);

    void movePaddle(float dx);

private:
    Quad background;
    Paddle paddle;
    Ball ball;
    BrickMap brickMap;
};
