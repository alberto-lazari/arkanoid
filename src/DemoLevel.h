#pragma once

#include "Level.h"

class DemoLevel : public Level
{
public:
    DemoLevel();

private:
    virtual std::vector<Brick> makeBrickMap() const override;
};
