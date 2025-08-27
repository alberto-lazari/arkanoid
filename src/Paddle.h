#pragma once

#include "Quad.h"

#include <memory>

class Paddle
{
public:
    static constexpr Quad::Params DEFAULT_QUAD_PARAMS = {
        .width = 0.7f,
        .height = 0.1f,
        .posY = -1.3f,
        .colors = {
            .tl = { 0.8f, 0.8f, 0.8f, 1.0f },
            .tr = { 0.8f, 0.8f, 0.8f, 1.0f },
            .bl = { 0.4f, 0.4f, 0.4f, 1.0f },
            .br = { 0.4f, 0.4f, 0.4f, 1.0f },
        },
    };

    Paddle(float speed = 5.0f, const Quad::Params& quadParams = DEFAULT_QUAD_PARAMS);

    constexpr const Quad& getQuad() const { return quad; }

    void move(float dx);
    void setPosition(float x);
    void update(float dt);
    void render(float aspectRatio, float alpha);

private:
    Quad quad;
    float moveSpeed;
};
