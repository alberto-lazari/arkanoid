#include "BrickMap.h"

#include "Brick.h"
#include "Quad.h"

#include <algorithm>
#include <utility>

BrickMap::BrickMap(Columns&& bricks)
{
    // std::sort(bricks);

    if (bricks.empty()) return;

    float rowY = bricks[0]->getQuad().getPosY();
    rows.emplace_back();
    for (auto& brickPtr : bricks)
    {
        const float brickY = brickPtr->getQuad().getPosY();

        if (brickY != rowY)
        {
            // Create a new row
            rows.emplace_back();
            rowY = brickY;
        }

        rows.back().push_back(std::move(brickPtr));
    }
}

void BrickMap::update(float dt)
{
    for (const auto& row : rows)
        for (const auto& brickPtr : row)
            brickPtr->update(dt);
}

void BrickMap::render(float aspectRatio, float alpha)
{
    for (const auto& row : rows)
        for (const auto& brickPtr : row)
            brickPtr->render(aspectRatio, alpha);
}

auto BrickMap::findBricksNearby(const Quad& quad)
    -> std::vector<std::pair<Rows::iterator, Columns::iterator>>
{
    if (rows.empty()) return {};

    const auto findNearestRows = 
        [this](float y) -> std::pair<Rows::iterator, Rows::iterator>
        {
            // Binary search for the first row whose Y is <= y
            const auto it = std::lower_bound(rows.begin(), rows.end(), y,
                [](const auto& row, float value)
                {
                    return row[0]->getQuad().getPosY() > value;
                });

            // y is above the top row
            if (it == rows.begin()) return { it, it };

            // y is below the bottom row
            if (it == rows.end()) return { it - 1, it - 1 };

            // y is between two rows
            return { it - 1, it };
        };

    const auto findNearestColumns =
        [](float x, Columns& row) -> std::pair<Columns::iterator, Columns::iterator>
        {
            // Binary search for the first column in row whose X is >= x
            const auto it = std::lower_bound(row.begin(), row.end(), x,
                [](const auto& brickPtr, float value)
                {
                    return brickPtr->getQuad().getPosX() < value;
                });

            // x is before the first column
            if (it == row.begin()) return { it, it };

            // x is after the last column
            if (it == row.end()) return { it - 1, it - 1 };

            // x is between two columns
            return { it - 1, it };
        };

    std::vector<std::pair<Rows::iterator, Columns::iterator>> bricks;
    const auto& [bottomRow, topRow] = findNearestRows(quad.getPosY());

    const auto& [bottomLeft, bottomRight] = findNearestColumns(quad.getPosX(), *bottomRow);
    bricks.push_back({ bottomRow, bottomRight });
    if (bottomLeft != bottomRight) bricks.push_back({ bottomRow, bottomLeft });

    if (bottomRow == topRow) return bricks;

    const auto& [topLeft, topRight] = findNearestColumns(quad.getPosX(), *topRow);
    bricks.push_back({ topRow, topRight });
    if (topLeft != topRight) bricks.push_back({ topRow, topLeft });

    return bricks;
}

void BrickMap::destroyBrick(const Rows::iterator& rowIt, const Columns::iterator& brickIt)
{
    Columns& row = *rowIt;
    row.erase(brickIt);
    if (row.empty()) rows.erase(rowIt);
}
