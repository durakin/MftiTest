#pragma once

class MovingObject
{
public:
    float speed_x;
    float speed_y;
    float x;
    float y;

    void move(float dt);
};
