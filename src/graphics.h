#pragma once
#include "SDL.h"
#include "viewport.h"
#include <vector>
#include <algorithm>

class ED_Viewport;
class ED_Bitmap;

namespace ED_Graphics
{
	// Private
	extern SDL_Surface* canvas;
	extern std::vector<ED_Viewport*> viewports;
	extern unsigned char* screen_buffer;
	extern int screen_brightness;
	extern bool need_sort;

	// Public
	extern int screen_width;
	extern int screen_height;
	extern int frame_rate;
	extern int frame_count;

	void init();
	void update();
	void wait(int time);
	void delay(int ms);
	ED_Bitmap* snap_to_bitmap();

	void resize_screen(int width, int height);

	void set_brightness(float value);
	int get_brightness();
}