#include <cstdint>

#include "PixelDigits.h"
#include "Engine.h"

char heart[29] = {
 "...."
 "##.#"
 "####"
 "###."
 ".#.."
 "...."
 "...."
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
			buffer[y0 + i][x0 + j] = color;
		}
	}
}

void draw_number(int number, int x0, int y0, int pixel_size, int space_size, uint32_t color)
{
	for (int r = 1; r <= 3; r++)
	{
		int digit_x0 = x0 - r * (pixel_size * 4 + space_size) + space_size;
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (digits[number % 10][i * 4 + j] == '#')
				{
					draw_pixel(i * pixel_size + y0, digit_x0 + j * pixel_size, pixel_size, color);
				}
			}
		}
		number /= 10;
	}
}

void draw_symbol(int x0, int y0, char symbol[29], uint32_t color)
{

}

