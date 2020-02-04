#include "graphics.h"
#include "ed_main.h"

SDL_Surface* ED_Graphics::canvas = 0;
std::vector<ED_Viewport*> ED_Graphics::viewports;
unsigned char* ED_Graphics::screen_buffer = 0;
int ED_Graphics::screen_width = 0;
int ED_Graphics::screen_height = 0;
int ED_Graphics::screen_brightness = 255;
bool ED_Graphics::need_sort = false;

int ED_Graphics::frame_rate = 60;
int ED_Graphics::frame_count = 0;

void ED_Graphics::init()
{
	screen_buffer = new unsigned char[screen_width * screen_height * 4];
	canvas = SDL_CreateRGBSurfaceWithFormatFrom((void*)screen_buffer, screen_width, screen_height,
		32, 4 * screen_width, SDL_PIXELFORMAT_RGBA32);
}

void ED_Graphics::update()
{
	SDL_FillRect(canvas, 0, SDL_MapRGBA(canvas->format, 0, 0, 0, 0));
	if (need_sort) {
		std::sort(viewports.begin(), viewports.end(), [](ED_Viewport* a, ED_Viewport* b) { return a->get_z() < b->get_z(); }); // < = ÉýÐò | > = ½µÐò
		need_sort = false;
	}
	for (auto iter = viewports.begin(); iter != viewports.end(); iter++) {
		if ((*iter)->visible)
			(*iter)->draw();
	}
	SDL_Rect src_rt;
	src_rt.x = 0;
	src_rt.y = 0;
	src_rt.w = screen_width;
	src_rt.h = screen_height;
	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(g_renderer, canvas);
	SDL_SetTextureAlphaMod(pTexture, screen_brightness);
	SDL_RenderClear(g_renderer);
	SDL_RenderCopy(g_renderer, pTexture, &src_rt, &src_rt);
	SDL_RenderPresent(g_renderer);
	SDL_DestroyTexture(pTexture);

	delay(1000 / frame_rate);
	frame_count += 1;
}

void ED_Graphics::wait(int time)
{
	for (int index = 0; index < time; index++)
		update();
}

void ED_Graphics::delay(int ms)
{
	SDL_Delay(ms);
}

static inline SDL_Surface* copy_surface(SDL_Surface* src)
{
	return SDL_ConvertSurface(src, src->format, SDL_SWSURFACE);
}

ED_Bitmap* ED_Graphics::snap_to_bitmap()
{
	ED_Bitmap* snap = new ED_Bitmap(copy_surface(ED_Graphics::canvas));
	return snap;
}

void ED_Graphics::resize_screen(int width, int height)
{
	SDL_FreeSurface(canvas);
	delete[]screen_buffer;
	screen_buffer = new unsigned char[width * height * 4];
	canvas = SDL_CreateRGBSurfaceWithFormatFrom((void*)screen_buffer, width, height,
		32, 4 * width, SDL_PIXELFORMAT_RGBA32);
	SDL_SetWindowSize(g_window, width, height);
	screen_width = width;
	screen_height = height;
}

void ED_Graphics::set_brightness(float value)
{
	screen_brightness = value;
}

int ED_Graphics::get_brightness()
{
	return screen_brightness;
}
