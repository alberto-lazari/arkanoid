#include "Level.h"

#include "Game.h"

Level::Level(std::vector<Brick>&& bricks)
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
    , brickMap(std::move(bricks))
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
            brickMap.destroyBrick(rowIt, brickIt);
        }
    }
}

void Level::movePaddle(float dx)
{
    paddle.move(dx);
}
