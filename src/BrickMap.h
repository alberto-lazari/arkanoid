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

    BrickMap(std::vector<Brick>&& bricks);

    void update(float dt);
    void render(float aspectRatio, float alpha);

    /**
     * Binary search up to four bricks which are nearest to the quad.
     * In the general case, the four bricks are { bottom-right, bottom-left, top-right, top-left }.
     * Bricks are guaranteed to be returned in the order shown above, which is the opposite of the
     * ordering of rows and columns. This way, bricks can safely be destroyed, without invalidating
     * next iterators.
     */
    std::vector<std::pair<Rows::iterator, Columns::iterator>> findBricksNearby(const Quad& quad);

    void destroyBrick(const Rows::iterator& rowIt, const Columns::iterator& brickIt);

private:
    Rows rows;
};
