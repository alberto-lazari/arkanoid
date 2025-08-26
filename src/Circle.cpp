#include "Circle.h"

Circle::Circle(float speed, const Params& quadParams)
    : Quad(quadParams)
    , moveSpeed(speed)
{
}
