#pragma once

#include "Brick.h"

#include <vector>
#include <memory>

class Quad;

class BrickMap
{
public:
    using Columns = std::vector<std::unique_ptr<Brick>>;
    using Rows = std::vector<Columns>;

    BrickMap(Columns&& bricks);

    void update(float dt);
    void render(float aspectRatio, float alpha);

    std::vector<std::pair<Rows::iterator, Columns::iterator>> findBricksNearby(const Quad& quad);
    void destroyBrick(const Rows::iterator& rowIt, const Columns::iterator& brickIt);

private:
    Rows rows;
};
