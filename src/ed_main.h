#pragma once
#include "SDL.h"
#include "graphics.h"

extern SDL_Renderer* g_renderer;
extern SDL_Window* g_window;

void Init_EasyDraw(int screen_width, int screen_height, const char *title);

void Final_EasyDraw();
