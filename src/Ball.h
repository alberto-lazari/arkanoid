#pragma once

#include "Circle.h"

class Ball
{
public:
    static constexpr Circle::Params DEFAULT_CIRCLE_PARAMS = {
        .posX = -1.5f,
        .posY = 0.0f,
        .colors = {
            .tl = { 1.0f, 1.0f, 1.0f, 1.0f },
            .tr = { 0.9f, 0.9f, 0.9f, 1.0f },
            .bl = { 0.8f, 0.8f, 0.8f, 1.0f },
            .br = { 0.4f, 0.4f, 0.4f, 1.0f },
        },
    };

    Ball(float speed = 3.0f, const Circle::Params& circleParams = DEFAULT_CIRCLE_PARAMS);

    constexpr const Circle& getQuad() const { return circle; }
    float getSpeed() const;

    void setPosition(float x, float y);
    void setSpeed(float speed);

    void update(float dt);
    void render(float aspectRatio, float alpha);

    void resolveCollisionWith(const Quad& other, const std::array<float, 2>& distance);
    void resolveCollisionWith(const Quad& other)
    {
        resolveCollisionWith(other, circle.distanceFrom(other));
    }

private:
    Circle circle;
    float velocity[2] = { 0.0f, 0.0f };
};
