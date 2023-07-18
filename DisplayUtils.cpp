#include <algorithm>

#include "DisplayUtils.h"
#include "Engine.h"


void set_color(int x, int y, uint32_t color)
{
	if ((x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)) {
		buffer[y][x] = color;
	}
};

void fill_screen(uint32_t color)
{
	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		std::fill_n(buffer[i], SCREEN_WIDTH, color);
	}
};
