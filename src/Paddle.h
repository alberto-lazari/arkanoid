#pragma once

#include "Rectangle.h"

class Paddle : public Rectangle
{
public:
    Paddle();

private:
    static constexpr Rectangle::Params rectangleParams = {
        .width = 0.4f,
        .height = 0.05f,
        .posY = -0.85f,
        .colors = {
            .tl = { 0.9f, 0.9f, 0.9f, 1.0f },
            .tr = { 0.9f, 0.9f, 0.9f, 1.0f },
            .bl = { 0.4f, 0.4f, 0.4f, 1.0f },
            .br = { 0.4f, 0.4f, 0.4f, 1.0f },
        },
    };
};
