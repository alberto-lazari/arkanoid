#pragma once

#include "Quad.h"

class Brick
{
public:
    static constexpr float WIDTH = 0.5f;
    static constexpr float HEIGHT = 0.15f;

    Brick(float posX, float posY, const Quad::Colors& colors);

    constexpr const Quad& getQuad() const { return quad; }

    void update(float dt);
    void render(float aspectRatio, float alpha);

private:
    Quad quad;
};
