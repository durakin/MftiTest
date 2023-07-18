#include <stdlib.h>
#include <memory.h>
#include <cmath>
#include <math.h>
#include <vector>
#include <algorithm>
#include <type_traits>

#include "Engine.h"
#include "DrawableObject.h"
#include "MovingObject.h"
#include "CollidableObject.h"
#include "Constants.h"
#include "GeometryUtils.h"
#include "EnemyRectangular.h"
#include "FriendlyCircle.h"
#include "Player.h"
#include "DisplayUtils.h"

//  is_key_pressed(int button_vk_code) - check if a key is pressed,
//                                       use keycodes (VK_SPACE, VK_RIGHT, VK_LEFT, VK_UP, VK_DOWN, 'A', 'B')
//
//  get_cursor_x(), get_cursor_y() - get mouse cursor position
//  is_mouse_button_pressed(int button) - check if mouse button is pressed (0 - left button, 1 - right button)
//  clear_buffer() - set all pixels in buffer to 'black'
//  is_window_active() - returns true if window is active
//  schedule_quit_game() - quit game after act()

std::vector<EnemyRectangular> enemies;
std::vector<FriendlyCircle> friendlies;


void move_player(float t, float& x1, float& y1, float& x2, float& y2) {
    x1 = PLAYZONE_RADIUS * std::cos(t) + SCREEN_WIDTH / 2;
    y1 = PLAYZONE_RADIUS * std::sin(t) + SCREEN_HEIGHT/ 2;
    draw_circle(x1, y1, PLAYER_RADIUS, WHITE_COLOR);
    x2 = PLAYZONE_RADIUS * std::cos(t + M_PI) + SCREEN_WIDTH/ 2;
    y2 = PLAYZONE_RADIUS * std::sin(t + M_PI) + SCREEN_HEIGHT / 2;
    draw_circle(x2, y2, PLAYER_RADIUS, WHITE_COLOR);
}

void draw_playzone() {
    draw_circle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, PLAYZONE_RADIUS, PLAYZONE_COLOR);
}

template <typename T>
void clear_inactive(std::vector<T> &objects) {
    static_assert(std::is_convertible_v<T&, DrawableObject&>);
    objects.erase(std::remove_if(objects.begin(), objects.end(), [](const T& elem) {
        return elem.active == false;
        }), objects.end());
}

void spawn_random_enemy(uint32_t color, int x, int y) {
    EnemyRectangular enemy;
    enemy.x = x;
    enemy.y = y;
    enemy.color = color;
    enemy.side_x = 80;
    enemy.side_y = 80;
    enemy.speed_x = 100;
    enemy.speed_y = 100;
    enemy.active = true;
    enemies.push_back(enemy);
}

void spawn_random_friend(uint32_t color, int x, int y) {
    FriendlyCircle friendly;
    friendly.x = x;
    friendly.y = y;
    friendly.color = color;
    friendly.radius = 30;
    friendly.speed_x = 100;
    friendly.speed_y = 100;
    friendly.active = true;
    friendlies.push_back(friendly);
}


// initialize game data in this function
void initialize()
{
    int player_x1 = SCREEN_WIDTH / 2 - PLAYZONE_RADIUS;
    int player_x2 = SCREEN_WIDTH / 2 + PLAYZONE_RADIUS;
    int player_y1 = SCREEN_HEIGHT / 2 - PLAYZONE_RADIUS;
    int player_y2 = SCREEN_HEIGHT / 2 + PLAYZONE_RADIUS;
    Player_circle first;
    first.x = player_x1;
    first.y = player_y1;
    Player_circle second;
    second.x = player_x2;
    second.y = player_y2;
    player.first = first;
    player.second = second;
    player.offset = 0;
    player.direction = 1;
    score = 0;
    enemy_pool = 0;
    spawn_random_enemy(1488, 100, 100);
    spawn_random_enemy(14888841, 150, 150);
    spawn_random_friend(84888841, 225, 225);
    spawn_random_enemy(14888841, 350, 350);
}

// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt)
{
    fill_screen(BACKSCREEN_COLOR);
    draw_playzone();

    if (is_key_pressed(VK_ESCAPE))
    {
        schedule_quit_game();
    }

    player.offset += (dt * PLAYER_SPEED) * player.direction;
    if (player.offset >= 2 * M_PI)
    {
        player.offset -= 2 * M_PI;
    }
    move_player(player.offset, player.first.x, player.first.y, player.second.x, player.second.y);

    for (EnemyRectangular& enemy : enemies) {
        enemy.move(dt);
        if (enemy.collidesPlayer())
        {
            enemy.active = false;
            enemy_pool++;
        }
        enemy.draw();

        
    }   

    if (enemy_pool >= 1)
    {
        spawn_random_enemy(14888841, 150, 150);
        enemy_pool--;
    }

    for (FriendlyCircle& friendly : friendlies) {
        friendly.move(dt);
        if (friendly.collidesPlayer())
        {
            friendly.active = false;
            score++;
            friendly_pool++;
        }

        friendly.draw();

        if (score >= 1000)
        {
            schedule_quit_game();
            return;
        }
    }

    if (friendly_pool >= 1)
    {
        spawn_random_friend(84888841, 225, 225);
        friendly_pool--;
    }

    clear_inactive(enemies);
    clear_inactive(friendlies);

    if (is_key_pressed(VK_LEFT)) 
    {
        player.direction = 1;
    }
    if (is_key_pressed(VK_RIGHT))
    {
        player.direction = -1;
    }
}

// fill buffer in this function
// uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH] - is an array of 32-bit colors (8 bits per R, G, B)
void draw()
{
}

// free game data in this function
void finalize()
{
}
