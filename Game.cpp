#include "Engine.h"
#include <stdlib.h>
#include <memory.h>
#include <cmath>
#include <math.h>
#include <vector>
#include <algorithm>

#define WHITE_COLOR 0xffffffff
#define PLAYZONE_COLOR 0x8032CD32
#define BACKSCREEN_COLOR 0
#define PLAYER_RADIUS 25
#define PLAYZONE_RADIUS 150
#define M_PI 3.14159265358979323846 
#define PLAYER_SPEED 2



class MovingRectangular
{
public:
    float speed_x;
    float speed_y;
    float x;
    float y;
    int side_x;
    int side_y;
    uint32_t color;
};

struct Player_circle 
{
    int x;
    int y;
};

struct Player
{
    Player_circle first;
    Player_circle second;
    float offset;
    int direction;
};

std::vector<MovingRectangular> enemies;

Player player;

//  is_key_pressed(int button_vk_code) - check if a key is pressed,
//                                       use keycodes (VK_SPACE, VK_RIGHT, VK_LEFT, VK_UP, VK_DOWN, 'A', 'B')
//
//  get_cursor_x(), get_cursor_y() - get mouse cursor position
//  is_mouse_button_pressed(int button) - check if mouse button is pressed (0 - left button, 1 - right button)
//  clear_buffer() - set all pixels in buffer to 'black'
//  is_window_active() - returns true if window is active
//  schedule_quit_game() - quit game after act()
void fill_backscreen() {
    memset(buffer, BACKSCREEN_COLOR, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(uint32_t));
}

void draw_circle(int center_x, int center_y, int radius, uint32_t color) {
    for (int y = center_y - radius; y <= center_y + radius; y++) 
    {
        for (int x = center_x - radius; x <= center_x + radius; x++)
        {
            int dx = x - center_x;
            int dy = y - center_y;
            int distance = dx * dx + dy * dy;
            if (distance <= radius * radius) 
            {
                buffer[y][x] = color;
            }
        }
    }
}

void draw_sqare(int center_x, int center_y, int side_x, int side_y, uint32_t color) 
{
    for (int y = center_y - side_y / 2; y <= center_y + side_y / 2; y++) {
        for (int x = center_x - side_x / 2; x <= center_x + side_x; x++) {
            if ((x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)) {
                buffer[y][x] = color;
            }
        }
    }
}

bool is_collision(MovingRectangular* object)
{
    
    return false;
}

void move_enemy(float t, MovingRectangular* enemy)
{
    enemy->x += (t * enemy->speed_x);
    enemy->y += (t * enemy->speed_y);
    draw_sqare(enemy->x, enemy->y, enemy->side_x, enemy->side_y, enemy->color);
}

void move_player(float t, int& x1, int& y1, int& x2, int& y2) {
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




void spawn_random_enemy(uint32_t color, int x, int y) {
    MovingRectangular enemy;
    enemy.x = x;
    enemy.y = y;
    enemy.color = color;
    enemy.side_x = 10;
    enemy.side_y = 15;
    enemy.speed_x = 100;
    enemy.speed_y = 100;
    enemies.push_back(enemy);
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
    int box_size = 5;
    spawn_random_enemy(1488, 100, 100);
    spawn_random_enemy(14888841, 350, 350);
}


// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt)
{
    fill_backscreen();
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

    for (MovingRectangular& enemy: enemies) {
        move_enemy(dt, &enemy);
    }

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
