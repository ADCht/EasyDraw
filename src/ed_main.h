#pragma once
#include "SDL.h"
#include "graphics.h"

typedef void(*ED_Exit)();
extern SDL_Renderer* g_renderer;
extern SDL_Window* g_window;
extern ED_Exit exit_event;

void Init_EasyDraw(int screen_width, int screen_height, const char *title, ED_Exit atexit);

void Final_EasyDraw();
