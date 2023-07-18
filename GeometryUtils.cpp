#include <algorithm>
#include <math.h>

#include "GeometryUtils.h"
#include "Engine.h"
#include "DisplayUtils.h"

#define SCREEN_DIAG 1280


struct LineEquation {
    float a;
    float b;
    float c;
};

LineEquation get_line_equation(float x1, float y1, float x2, float y2)
{
    LineEquation result;
    result.a = y2 - y1;
    result.b = x1 - x2;
    result.c = (y1 * x2) - (x1 * y2);
    return result;
}

float distance_line_circle(LineEquation line, float c_x, float c_y)
{
    return abs(line.a * c_x + line.b * c_y + line.c) / sqrt(line.a * line.a + line.b * line.b);
}

float dot_product(float x1, float y1, float x2, float y2, float i1, float j1, float i2, float j2)
{
    return (x2 - x1) * (i2 - i1) + (y2 - y1) * (j2 - j1);
}

float distance_dot_dot(float x1, float y1, float x2, float y2)
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

bool is_collision_circle_rectangular(float radius, float c_x, float c_y, float r_x1, float r_y1, float r_x2, float r_y2, float r_x3, float r_y3, float r_x4, float r_y4)
{
    LineEquation line1 = get_line_equation(r_x1, r_y1, r_x2, r_y2);
    LineEquation line2 = get_line_equation(r_x2, r_y2, r_x3, r_y3);
    LineEquation line3 = get_line_equation(r_x3, r_y3, r_x4, r_y4);
    LineEquation line4 = get_line_equation(r_x4, r_y4, r_x1, r_y1);

    return (distance_line_circle(line1, c_x, c_y) <= radius
        && dot_product(r_x1, r_y1, r_x2, r_y2, r_x1, r_y1, c_x, c_y) >= 0
        && dot_product(r_x2, r_y2, r_x1, r_y1, r_x2, r_y2, c_x, c_y) >= 0
        || distance_line_circle(line2, c_x, c_y) <= radius
        && dot_product(r_x2, r_y2, r_x3, r_y3, r_x2, r_y2, c_x, c_y) >= 0
        && dot_product(r_x3, r_y3, r_x2, r_y2, r_x3, r_y3, c_x, c_y) >= 0
        || distance_line_circle(line3, c_x, c_y) <= radius
        && dot_product(r_x3, r_y3, r_x4, r_y4, r_x3, r_y3, c_x, c_y) >= 0
        && dot_product(r_x4, r_y4, r_x3, r_y3, r_x4, r_y4, c_x, c_y) >= 0
        || distance_line_circle(line4, c_x, c_y) <= radius
        && dot_product(r_x4, r_y4, r_x1, r_y1, r_x4, r_y4, c_x, c_y) >= 0
        && dot_product(r_x1, r_y1, r_x4, r_y4, r_x1, r_y1, c_x, c_y) >= 0)
        || distance_dot_dot(c_x, c_y, r_x1, r_y1) <= radius
        || distance_dot_dot(c_x, c_y, r_x2, r_y2) <= radius
        || distance_dot_dot(c_x, c_y, r_x3, r_y3) <= radius
        || distance_dot_dot(c_x, c_y, r_x4, r_y4) <= radius
        ;
}

bool is_collision_circle_circle(float x1, float y1, float x2, float y2, float r1, float r2)
{
    return ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) <= (r1 + r2) * (r1 + r2);
}

bool is_out_of_playzone_circle(float x, float y, float radius) {
    return false;
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
                set_color(x, y, color);
            }
        }
    }
}

void draw_sqare(float center_x, float center_y, float side_x, float side_y, uint32_t color)
{
    for (int y = center_y - side_y / 2; y <= center_y + side_y / 2; y++) {
        for (int x = center_x - side_x / 2; x <= center_x + side_x / 2; x++) {
            set_color(x, y, color);
        }
    }
}

void findTangents(float c_x,float x_y, float c_r, float p_x, float p_y) {
    /*double dx = p_x - circle.center.x;
    double dy = p_y - circle.center.y;
    double d = sqrt(dx * dx + dy * dy);
    double theta = atan2(dy, dx);
    double alpha = asin(circle.radius / d);

    double commonTangent1 = theta + alpha;
    double commonTangent2 = theta - alpha;
    double directTangent1 = theta + (PI / 2) + alpha;
    double directTangent2 = theta + (PI / 2) - alpha;

    std::cout << "Common Tangents: (" << cos(commonTangent1) * circle.radius + circle.center.x << ", "
        << sin(commonTangent1) * circle.radius + circle.center.y << ") and ("
        << cos(commonTangent2) * circle.radius + circle.center.x << ", "
        << sin(commonTangent2) * circle.radius + circle.center.y << ")" << std::endl;

    std::cout << "Direct Tangents: (" << cos(directTangent1) * circle.radius + circle.center.x << ", "
        << sin(directTangent1) * circle.radius + circle.center.y << ") and ("
        << cos(directTangent2) * circle.radius + circle.center.x << ", "
        << sin(directTangent2) * circle.radius + circle.center.y << ")" << std::endl;
        */
}