#pragma once

bool is_collision_circle_rectangular(float radius, float c_x, float c_y, float r_x1, float r_y1, float r_x2, float r_y2, float r_x3, float r_y3, float r_x4, float r_y4);

bool is_collision_circle_circle(float x1, float y1, float x2, float y2, float r1, float r2);

void draw_circle(int center_x, int center_y, int radius, uint32_t color);

void draw_sqare(float center_x, float center_y, float side_x, float side_y, uint32_t color);
