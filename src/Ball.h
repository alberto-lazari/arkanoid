#pragma once

#include "Circle.h"

#include <memory>

class Ball
{
public:
    static constexpr Circle::Params DEFAULT_CIRCLE_PARAMS = {
        .posY = 0.0f,
        .posX = -1.5f,
        .colors = {
            .tl = { 1.0f, 1.0f, 1.0f, 1.0f },
            .tr = { 0.7f, 0.7f, 0.7f, 1.0f },
            .bl = { 0.5f, 0.6f, 0.6f, 1.0f },
            .br = { 0.3f, 0.3f, 0.3f, 1.0f },
        },
    };

    Ball(float speed = 3.0f, const Circle::Params& circleParams = DEFAULT_CIRCLE_PARAMS);

    void update(float dt);
    void render(float aspectRatio, float alpha);
    void resolveCollisionWith(const Quad& other);

private:
    std::unique_ptr<Circle> circle;
    float moveSpeed;
    float velocity[2] = { 0.0f, 0.0f };
};
