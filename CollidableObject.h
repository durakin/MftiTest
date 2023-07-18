#pragma once

class CollidableObject
{
public:
    virtual bool collides_player() = 0;
    virtual bool out_of_playzone() = 0;
};
