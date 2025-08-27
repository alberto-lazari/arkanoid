#include "Ball.h"

#include "Game.h"

#include <cmath>

Ball::Ball(float speed, const Circle::Params& circleParams)
    : circle(std::make_unique<Circle>(circleParams))
    , moveSpeed(speed)
    , velocity { speed, -speed }
{
}

void Ball::update(float dt)
{
    circle->move(dt * velocity[0], dt * velocity[1]);

    const float ray = circle->getRay();
    auto resolveWallCollision = [&](float& pos, float& velocity, float halfWorldSize)
    {
        if (std::abs(pos) + ray >= halfWorldSize)
        {
            pos = std::copysign(halfWorldSize - ray, pos);
            velocity *= -1.0f;
        }
    };

    // Check if hitting walls
    float posX = circle->getPosX();
    resolveWallCollision(posX, velocity[0], Game::WIDTH / 2.0f);
    circle->setPositionX(posX);

    float posY = circle->getPosY();
    resolveWallCollision(posY, velocity[1], Game::HEIGHT / 2.0f);
    circle->setPositionY(posY);

    circle->update(dt);
}

void Ball::render(float aspectRatio, float alpha)
{
    circle->render(aspectRatio, alpha);
}

void Ball::resolveCollisionWith(const Quad& other)
{
    const auto& distance = circle->distanceFrom(other);
    const auto& [distX, distY] = distance;

    // Check if the quads are actually colliding
    if (distX > 0.0f || distY > 0.0f) return;

    // Push ball outside of the quad
    circle->resolveCollisionWith(other, distance);

    // Update velocity to match the impact
    velocity[distX < distY ? 0 : 1] *= -1.0f;
}
