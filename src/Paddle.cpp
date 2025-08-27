#include "Paddle.h"

#include "Game.h"

Paddle::Paddle(float speed, const Quad::Params& quadParams)
    : quad { quadParams }
    , moveSpeed(speed)
{
}

void Paddle::move(float dx)
{
    const float movement = dx * moveSpeed;

    // Check if hitting walls
    const float posX = quad.getPosX();
    const float halfWidth = quad.getWidth() / 2.0f;
    const float halfWorldWidth = Game::WIDTH / 2.0f;
    if (posX + movement + halfWidth >= halfWorldWidth)
    {
        setPosition(halfWorldWidth - halfWidth);
        return;
    }
    if (posX + movement - halfWidth <= -halfWorldWidth)
    {
        setPosition(-halfWorldWidth + halfWidth);
        return;
    }

    quad.move(movement, 0.0f);
}

void Paddle::setPosition(float x)
{
    quad.setPositionX(x);
}

void Paddle::update(float dt)
{
    quad.update(dt);
}

void Paddle::render(float aspectRatio, float alpha)
{
    quad.render(aspectRatio, alpha);
}
