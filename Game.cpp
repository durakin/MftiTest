#include <stdlib.h>
#include <memory.h>
#include <cmath>
#include <math.h>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <random>

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
#include "PixelDigits.h"

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

void set_random_speed_vector(float start_x, float start_y, float &speed_x, float &speed_y)
{
    float playzone_x = SCREEN_WIDTH / 2;
    float playzone_y = SCREEN_HEIGHT / 2;

    float speed_coeff = MIN_ENEMY_SPEED + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (MAX_ENEMY_SPEED - MIN_ENEMY_SPEED)));
    float y_coeff = MIN_ENEMY_SPEED_Y + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (MAX_ENEMY_SPEED_Y - MIN_ENEMY_SPEED_Y)));

    speed_x = (playzone_x - start_x) * speed_coeff;
    speed_y = (playzone_y - start_y) * speed_coeff * y_coeff;
}

void set_random_spawnpoint(float& y)
{
    y = MIN_ENEMY_SPAWN_Y + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (MAX_ENEMY_SPAWN_Y - MIN_ENEMY_SPAWN_Y)));
}

void set_random_enemy_size(float& size_x, float& size_y)
{
    size_x = MIN_ENEMY_SIZE + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (MAX_ENEMY_SIZE - MIN_ENEMY_SIZE)));
    size_y = size_x;
}

void set_random_friendly_radius(float& radius)
{
    radius = MIN_FRIENDLY_RADIUS + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (MAX_FRIENDLY_RADIUS - MIN_FRIENDLY_RADIUS)));
}

void spawn_random_enemy(uint32_t color) {
    EnemyRectangular enemy;
    enemy.color = color;
    enemy.x = SPAWN_X;

    set_random_enemy_size(enemy.side_x, enemy.side_y);
    set_random_spawnpoint(enemy.y);
    set_random_speed_vector(enemy.x, enemy.y, enemy.speed_x, enemy.speed_y);

    enemy.active = true;
    enemies.push_back(enemy);
    enemy_cooldown = ENEMY_COOLDOWN;
}

void spawn_random_friend(uint32_t color) {
    FriendlyCircle friendly;
    friendly.color = color;
    friendly.x = SPAWN_X;

    set_random_spawnpoint(friendly.y);
    set_random_friendly_radius(friendly.radius);
    set_random_speed_vector(friendly.x, friendly.y, friendly.speed_x, friendly.speed_y);

    friendly.active = true;
    friendlies.push_back(friendly);
    friendly_cooldown = FRIENDLY_COOLDOWN;
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
    hp = INITIAL_HP;
    enemy_pool = ENEMY_POOL;
    friendly_pool = FRIENDLY_POOL;
    friendly_cooldown = 0;
    enemy_cooldown = 0;
    srand(time(0));
}

// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt)
{
    friendly_cooldown -= dt;
    enemy_cooldown -= dt;

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
        if (enemy.out_of_playzone())
        {
            enemy.active = false;
            enemy_pool++;
        }
        if (enemy.collidesPlayer())
        {
            hp--;
            enemy.active = false;
            enemy_pool++;
        }
        enemy.draw();
    }   

    if (enemy_pool >= 1 && enemy_cooldown <= 0)
    {
        spawn_random_enemy(14888841);
        enemy_pool--;
    }

    for (FriendlyCircle& friendly : friendlies) {
        friendly.move(dt);

        if (friendly.out_of_playzone())
        {
            friendly.active = false;
            friendly_pool++;
        }

        if (friendly.collidesPlayer())
        {
            friendly.active = false;
            score++;
            if (score % BONUS_HP_SCORE == 0)
            {
                hp++;
            }
            friendly_pool++;
        }
        
        friendly.draw();

        draw_number(score, 600, 120, 4, 2, WHITE_COLOR);
        draw_hp(hp, 700, 120, 4, 2, WHITE_COLOR, WHITE_COLOR);

        if (score >= 1000)
        {
            schedule_quit_game();
            return;
        }
    }

    if (friendly_pool >= 1 && friendly_cooldown <= 0)
    {
        spawn_random_friend(84888841);
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

    if (hp <= 0)
    {
        schedule_quit_game();
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
