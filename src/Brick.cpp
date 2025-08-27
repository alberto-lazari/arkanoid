#include "Brick.h"

Brick::Brick(float posX, float posY, const Quad::Colors& colors)
    : quad({
        .posX = posX,
        .posY = posY,
        .width = WIDTH,
        .height = HEIGHT,
        .colors = colors,
    })
{
}

void Brick::update(float dt)
{
    quad.update(dt);
}

void Brick::render(float aspectRatio, float alpha)
{
    quad.render(aspectRatio, alpha);
}
