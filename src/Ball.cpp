#include "Ball.h"

Ball::Ball(float speed, const Quad::Params& quadParams)
    : circle(std::make_unique<Circle>(quadParams))
    , moveSpeed(speed)
    , velocity { speed, -speed }
{
}

void Ball::update(float dt)
{
    // Check if hitting walls
    const float posX = circle->getPosX();
    const float halfWidth = circle->getWidth() / 2.0;
    if (posX + halfWidth >= 1.0 || posX - halfWidth <= -1.0)
        velocity[0] *= -1;

    const float posY = circle->getPosY();
    const float halfHeight = circle->getHeight() / 2.0;
    if (posY + halfHeight >= 1.0 || posY - halfHeight <= -1.0)
        velocity[1] *= -1;

    circle->move(dt * velocity[0], dt * velocity[1]);
    circle->update(dt);
}

void Ball::render(float aspectRatio, float alpha)
{
    circle->render(aspectRatio, alpha);
}
