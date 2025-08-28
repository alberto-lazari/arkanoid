#include "DemoLevel.h"

DemoLevel::DemoLevel()
    : Level(makeBrickMap())
{
}

std::vector<Brick> DemoLevel::makeBrickMap() const
{
    std::vector<Brick> bricks;
    bricks.push_back({ 0, 0, {} });
    return bricks;
}
