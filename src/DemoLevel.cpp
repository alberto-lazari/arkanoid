#include "DemoLevel.h"

DemoLevel::DemoLevel()
    : Level(makeBrickMap(), 1)
{
}

std::vector<Brick> DemoLevel::makeBrickMap() const
{
    std::vector<Brick> bricks;

    constexpr int cols = 6;
    constexpr int rows = 5;
    constexpr float gapX = 0.05f;
    constexpr float gapY = 0.05f;
    constexpr float offsetY = 0.75f;

    constexpr float gridWidth  = cols * Brick::WIDTH + (cols - 1) * gapX;
    constexpr float gridHeight = rows * Brick::HEIGHT + (rows - 1) * gapY;

    // Start positions so that grid is centered
    constexpr float startX = -gridWidth  / 2.0f + Brick::WIDTH  / 2.0f;
    constexpr float startY =  gridHeight / 2.0f - Brick::HEIGHT / 2.0f + offsetY;

    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            // Compute position
            const float x = startX + col * (Brick::WIDTH + gapX);
            const float y = startY - row * (Brick::HEIGHT + gapY);

            // Simple rainbow color based on row/column
            const float r = static_cast<float>(col) / (cols - 1);
            const float g = static_cast<float>(row) / (rows - 1);
            const float b = 1.0f - static_cast<float>(col) / (cols - 1);

            Quad::Colors colors = {
                .tl = { r, g, b, 1.0f },
                .tr = { r, g, b, 1.0f },
                .bl = { r - 0.2f, g - 0.2f, b - 0.2f, 1.0f },
                .br = { r - 0.2f, g - 0.2f, b - 0.2f, 1.0f },
            };

            bricks.emplace_back(x, y, colors);
        }
    }

    return bricks;
}
