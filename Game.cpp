#include "Engine.h"
#include <stdlib.h>
#include <memory.h>
#include <cmath>
#include <math.h>

#define WHITE_COLOR 0xffffffff
#define PLAYZONE_COLOR 0x8032CD32
#define BACKSCREEN_COLOR 0
#define PLAYER_RADIUS 25
#define PLAYZONE_RADIUS 150
#define M_PI 3.14159265358979323846  /* pi */
#define PLAYER_SPEED 5

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
    for (int y = center_y - radius; y <= center_y + radius; y++) {
        for (int x = center_x - radius; x <= center_x + radius; x++) {
            int dx = x - center_x;
            int dy = y - center_y;
            int distanceSquared = dx * dx + dy * dy;
            if (distanceSquared <= radius * radius) {
                buffer[y][x] = color;
            }
        }
    }
}


void draw_player(float t, int& x1, int& y1, int& x2, int& y2) {
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

int player_x1 = SCREEN_WIDTH / 2 - PLAYZONE_RADIUS;
int player_x2 = SCREEN_WIDTH / 2 + PLAYZONE_RADIUS;
int player_y1 = SCREEN_HEIGHT / 2 - PLAYZONE_RADIUS;
int player_y2 = SCREEN_HEIGHT / 2 + PLAYZONE_RADIUS;
float player_offset = 0;
int direction = 1;

// initialize game data in this function
void initialize()
{
    int box_size = 5;
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
    player_offset += (dt * PLAYER_SPEED) * direction;

    draw_player(player_offset / M_PI, player_x1, player_y1, player_x2, player_y2);

    if (is_key_pressed(VK_LEFT)) 
    {
        direction = 1;
    }
    if (is_key_pressed(VK_RIGHT))
    {
        direction = -1;
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
