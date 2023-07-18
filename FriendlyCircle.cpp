#include "FriendlyCircle.h"
#include "GeometryUtils.h"
#include "Constants.h"
#include "Player.h"

void FriendlyCircle::draw() {
    if (active) {
        draw_circle(x, y, radius, color);
    }
}

bool FriendlyCircle::collidesPlayer()
{
    return is_collision_circle_circle(x, y, player.first.x, player.first.y, radius, PLAYER_RADIUS)
        || is_collision_circle_circle(x, y, player.second.x, player.second.y, radius, PLAYER_RADIUS);
}
