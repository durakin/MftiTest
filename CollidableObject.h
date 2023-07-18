#pragma once

class CollidableObject
{
public:
    virtual bool collidesPlayer() = 0;
    virtual bool out_of_playzone() = 0;
};
