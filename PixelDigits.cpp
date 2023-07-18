#include <cstdint>

#include "PixelDigits.h"
#include "DisplayUtils.h"
#include "Engine.h"

char heart[36] = {
 "....."
 "##.##"
 "#####"
 "#####"
 ".###."
 "..#.."
 "....."
};

char digits[10][29] = {
 "####"
 "#..#"
 "#..#"
 "#..#"
 "#..#"
 "#..#"
 "####",

 "..#."
 "..#."
 "..#."
 "..#."
 "..#."
 "..#."
 "..#.",

 "####"
 "...#"
 "...#"
 "####"
 "#..."
 "#..."
 "####",

 "####"
 "...#"
 "...#"
 "####"
 "...#"
 "...#"
 "####",

 "#..#"
 "#..#"
 "#..#"
 "####"
 "...#"
 "...#"
 "...#",

 "####"
 "#..."
 "#..."
 "####"
 "...#"
 "...#"
 "####",

 "####"
 "#..."
 "#..."
 "####"
 "#..#"
 "#..#"
 "####",

 "####"
 "...#"
 "...#"
 "...#"
 "...#"
 "...#"
 "...#",

 "####"
 "#..#"
 "#..#"
 "####"
 "#..#"
 "#..#"
 "####",

 "####"
 "#..#"
 "#..#"
 "####"
 "...#"
 "...#"
 "####"
};

void draw_pixel(int y0, int x0, int pixel_size, uint32_t color)
{
	for (int i = 0; i < pixel_size; i++)
	{
		for (int j = 0; j < pixel_size; j++) {
			set_color(x0 + j, y0 + i, color);
		}
	}
}

void draw_symbol(int x0, int y0, int pixel_size, int width, char symbol[29], uint32_t color)
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (symbol[i * width + j] == '#')
			{
				draw_pixel(i * pixel_size + y0, x0 + j * pixel_size, pixel_size, color);
			}
		}
	}
}

void draw_number(int number, int x0, int y0, int pixel_size, int space_size, uint32_t color)
{
	for (int r = 1; r <= 3; r++)
	{
		int digit_x0 = x0 + (3 - r) * (pixel_size * 4 + space_size) + space_size;
		draw_symbol(digit_x0, y0, pixel_size, 4, digits[number % 10], color);
		number /= 10;
	}
}

void draw_hp(int hp, int x0, int y0, int pixel_size, int space_size, uint32_t digits_color, uint32_t symbol_color) {
	draw_symbol(x0, y0, pixel_size, 5, heart, symbol_color);
	draw_number(hp, x0 + pixel_size * 5, y0, pixel_size, space_size, digits_color);
}
