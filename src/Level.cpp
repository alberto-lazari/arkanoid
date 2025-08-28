#include "Level.h"

#include "Game.h"

Level::Level(std::vector<Brick>&& bricks, unsigned int lives)
    : background({
        .width = Game::WIDTH,
        .height = Game::HEIGHT,
        .colors = {
            .tl = { 0.1f, 0.1f, 0.4f, 1.0f },
            .tr = { 0.1f, 0.1f, 0.4f, 1.0f },
            .bl = { 0.0f, 0.0f, 0.1f, 1.0f },
            .br = { 0.0f, 0.0f, 0.1f, 1.0f },
        },
    })
    , ball(0.0f)
    , brickMap(std::move(bricks))
    , lives(lives)
{
}

void Level::render(float aspectRatio, float alpha)
{
    background.render(aspectRatio, alpha);
    ball.render(aspectRatio, alpha);
    paddle.render(aspectRatio, alpha);
    brickMap.render(aspectRatio, alpha);
}

void Level::update(float dt)
{
    paddle.update(dt);
    ball.update(dt);

    if (ball.getSpeed() <= 0.0f)
    {
        const Quad& paddleQuad = paddle.getQuad();
        const float ballY = paddleQuad.getPosY() + paddleQuad.getHeight() / 2.0f + ball.getQuad().getRay();
        ball.setPosition(paddleQuad.getPosX(), ballY);

        // Skip ball collision checks
        return;
    }

    ball.resolveCollisionWith(paddle.getQuad());

    // Brick collisions
    const Quad& ballQuad = ball.getQuad();
    for (const auto& [rowIt, brickIt] : brickMap.findBricksNearby(ballQuad))
    {
        const Quad& brickQuad = (*brickIt)->getQuad();
        const auto& distance = ballQuad.distanceFrom(brickQuad);
        if (distance[0] <= 0 && distance[1] <= 0)
        {
            ball.resolveCollisionWith(brickQuad, distance);
            // It's safe to destroy here, because 'BrickMap::findBricksNearby' guarantees
            // that bricks are returned in reverse order.
            brickMap.destroyBrick(rowIt, brickIt);
        }
    }

    // Check if ball reached the bottom of the game
    if (ballQuad.getPosY() - ballQuad.getHeight() / 2.0f <= -Game::HEIGHT / 2.0f)
    {
        --lives;
        ball.setSpeed(0.0f);
    }
}

void Level::movePaddle(float dx)
{
    paddle.move(dx);
}

void Level::start()
{
    ball.setSpeed(getBallSpeed());
}

bool Level::gameOver() const
{
    return lives <= 0 || brickMap.allDestroyed();
}
