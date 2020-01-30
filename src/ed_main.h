#pragma once
#include "SDL.h"
#include "graphics.h"

extern SDL_Renderer* g_renderer;
extern SDL_Window* g_window;

void Init_EasyDraw(int screen_width, int screen_height);

void Final_EasyDraw();
