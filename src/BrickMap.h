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

    BrickMap();

    void update(float dt);
    void render(float aspectRatio, float alpha);

    std::vector<Columns::iterator> findBricksNearby(const Quad& quad);

private:
    Rows rows;
};
