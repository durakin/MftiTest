#include "MovingObject.h"

void MovingObject::move(float dt)
{
    x += (dt * speed_x);
    y += (dt * speed_y);
}
