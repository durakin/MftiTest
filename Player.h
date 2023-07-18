#pragma once

struct Player_circle
{
    float x;
    float y;
};

struct Player
{
    Player_circle first;
    Player_circle second;
    float offset;
    int direction;
};

extern Player player;
extern int score;
extern int enemy_pool;
extern int friendly_pool;
extern float enemy_cooldown;
extern float friendly_cooldown;
extern int hp;
extern bool space_pressed_lastframe;
