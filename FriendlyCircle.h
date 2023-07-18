#pragma once

#include <cstdint>

#include "MovingObject.h"
#include "CollidableObject.h"
#include "DrawableObject.h"

class FriendlyCircle : public MovingObject, public CollidableObject, public DrawableObject
{
public:
	float radius;
	uint32_t color;
	void draw() override;
	bool collidesPlayer() override;
	bool out_of_playzone() override;
};
