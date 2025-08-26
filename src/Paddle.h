#pragma once

#include "Rectangle.h"

#include <memory>

class Paddle
{
public:
    Paddle(float speed = 2.5f, const Rectangle::Params& rectangleParams = DEFAULT_PARAMS);

    void move(float dx);
    void setPosition(float x);
    void update(float dt);
    void render(float aspectRatio, float alpha);

private:
    std::unique_ptr<Rectangle> rectangle;
    float moveSpeed;

    static constexpr Rectangle::Params DEFAULT_PARAMS = {
        .width = 0.5f,
        .height = 0.08f,
        .posY = -0.85f,
        .colors = {
            .tl = { 0.9f, 0.9f, 0.9f, 1.0f },
            .tr = { 0.9f, 0.9f, 0.9f, 1.0f },
            .bl = { 0.4f, 0.4f, 0.4f, 1.0f },
            .br = { 0.4f, 0.4f, 0.4f, 1.0f },
        },
    };
};
