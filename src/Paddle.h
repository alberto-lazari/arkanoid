#pragma once

#include "Quad.h"

#include <memory>

class Paddle
{
public:
    static constexpr Quad::Params DEFAULT_QUAD_PARAMS = {
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

    Paddle(float speed = 2.5f, const Quad::Params& quadParams = DEFAULT_QUAD_PARAMS);

    void move(float dx);
    void setPosition(float x);
    void update(float dt);
    void render(float aspectRatio, float alpha);

private:
    std::unique_ptr<Quad> quad;
    float moveSpeed;
};
