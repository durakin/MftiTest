#pragma once

#include <cstdint>

#include "MovingObject.h"
#include "CollidableObject.h"
#include "DrawableObject.h"


class EnemyRectangular : public MovingObject, public CollidableObject, public DrawableObject
{
public:
    float side_x;
    float side_y;
    uint32_t color;
    void draw() override;
    bool collides_player() override;
    bool out_of_playzone() override;
};
