#include "Paddle.h"

Paddle::Paddle(float speed, const Quad::Params& quadParams)
    : quad(std::make_unique<Quad>(quadParams))
    , moveSpeed(speed)
{
}

void Paddle::move(float dx)
{
    quad->move(dx * moveSpeed);
}

void Paddle::setPosition(float x)
{
    quad->setPosition(x);
}

void Paddle::update(float dt)
{
    quad->update(dt);
}

void Paddle::render(float aspectRatio, float alpha)
{
    quad->render(aspectRatio, alpha);
}
