#include "FriendlyCircle.h"
#include "GeometryUtils.h"
#include "Constants.h"
#include "Player.h"
#include "Engine.h"

void FriendlyCircle::draw() {
    if (active) {
        draw_circle(x, y, radius, color);
    }
}

bool FriendlyCircle::collides_player()
{
    return is_collision_circle_circle(x, y, player.first.x, player.first.y, radius, PLAYER_RADIUS)
        || is_collision_circle_circle(x, y, player.second.x, player.second.y, radius, PLAYER_RADIUS);
}

bool FriendlyCircle::out_of_playzone()
{
    return x - radius > SCREEN_WIDTH;
}
