#include "Circle.h"

Circle::Circle(float speed, const Params& params)
    : Rectangle(params)
    , moveSpeed(speed)
{
}
