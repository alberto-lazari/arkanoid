#pragma once

#include "Circle.h"

#include <memory>

class Ball
{
public:
    Ball(float speed = 1.5f, const Quad::Params& quadParams = Circle::DEFAULT_QUAD_PARAMS);

    void update(float dt);
    void render(float aspectRatio, float alpha);

private:
    std::unique_ptr<Circle> circle;
    float moveSpeed;
    float velocity[2] = { 0.0f, 0.0f };
};
