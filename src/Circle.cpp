#include "Circle.h"

Circle::Circle(const Params& params)
    : Quad({
        .width = params.ray * 2.0f,
        .height = params.ray * 2.0f,
        .posX = params.posX,
        .posY = params.posY,
        .colors = params.colors,
        .fragmentShader = params.fragmentShader,
    })
{
}
