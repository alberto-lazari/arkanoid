#include "Paddle.h"

Paddle::Paddle(float speed, const Rectangle::Params& rectangleParams)
    : rectangle(std::make_unique<Rectangle>(rectangleParams))
    , moveSpeed(speed)
{
}

void Paddle::move(float dx)
{
    rectangle->move(dx * moveSpeed);
}

void Paddle::setPosition(float x)
{
    rectangle->setPosition(x);
}

void Paddle::update(float dt)
{
    rectangle->update(dt);
}

void Paddle::render(float aspectRatio, float alpha)
{
    rectangle->render(aspectRatio, alpha);
}
