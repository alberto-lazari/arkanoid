#include "Ball.h"

#include "Game.h"

#include <cmath>

Ball::Ball(float speed, const Circle::Params& circleParams)
    : circle { circleParams }
    , velocity { speed, -speed }
{
}

float Ball::getSpeed() const
{
    // Return average speed
    return (std::abs(velocity[0]) + std::abs(velocity[1])) / 2.0f;
}

void Ball::setPosition(float x, float y)
{
    circle.setPositionX(x);
    circle.setPositionY(y);
}

void Ball::setSpeed(float speed)
{
    velocity[0] = std::copysign(speed, velocity[0]);
    velocity[1] = std::copysign(speed, velocity[1]);
}

void Ball::update(float dt)
{
    circle.move(dt * velocity[0], dt * velocity[1]);

    const float ray = circle.getRay();
    auto resolveWallCollision = [&](float& pos, float& velocity, float halfWorldSize)
    {
        if (std::abs(pos) + ray >= halfWorldSize)
        {
            pos = std::copysign(halfWorldSize - ray, pos);
            velocity *= -1.0f;
        }
    };

    // Check if hitting walls
    float posX = circle.getPosX();
    resolveWallCollision(posX, velocity[0], Game::WIDTH / 2.0f);
    circle.setPositionX(posX);

    float posY = circle.getPosY();
    resolveWallCollision(posY, velocity[1], Game::HEIGHT / 2.0f);
    circle.setPositionY(posY);

    circle.update(dt);
}

void Ball::render(float aspectRatio, float alpha)
{
    circle.render(aspectRatio, alpha);
}

void Ball::resolveCollisionWith(const Quad& other, const std::array<float, 2>& distance)
{
    const auto& [distX, distY] = distance;

    // Check if the quads are actually colliding
    if (distX > 0.0f || distY > 0.0f) return;

    // Push ball outside of the quad and update velocity to match the impact
    if (std::abs(distX) < std::abs(distY))
    {
        circle.move(
            std::copysign(distX, circle.getPosX() - other.getPosX()),
            0.0f
        );
        velocity[0] *= -1.0f;
    }
    else
    {
        circle.move(
            0.0f,
            std::copysign(distY, circle.getPosY() - other.getPosY())
        );
        velocity[1] *= -1.0f;
    }
}
