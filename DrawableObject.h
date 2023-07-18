#pragma once

class DrawableObject
{
private:
public:
    virtual void draw() = 0;
    bool active = true;
};
