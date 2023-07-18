#include "Player.h"
#include "EnemyRectangular.h"
#include "Constants.h"
#include "GeometryUtils.h"
#include "Engine.h"

void EnemyRectangular::draw() {
    if (active) {
        draw_sqare(x, y, side_x, side_y, color);
    }
}

bool EnemyRectangular::collides_player()
{
    float x1 = x + side_x / 2;
    float y1 = y + side_y / 2;
    float x2 = x1;
    float y2 = y - side_y / 2;
    float x3 = x - side_x / 2;
    float y3 = y2;
    float x4 = x3;
    float y4 = y1;

    return is_collision_circle_rectangular(PLAYER_RADIUS, player.first.x, player.first.y, x1, y1, x2, y2, x3, y3, x4, y4)
        || is_collision_circle_rectangular(PLAYER_RADIUS, player.second.x, player.second.y, x1, y1, x2, y2, x3, y3, x4, y4);
}

bool EnemyRectangular::out_of_playzone()
{
    return x - side_x / 2 > SCREEN_WIDTH;
}