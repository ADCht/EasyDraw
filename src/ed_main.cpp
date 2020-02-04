#include "ed_main.h"
#include "SDL_opengl.h"
#include "SDL_ttf.h"
#include "SDL_image.h"

SDL_Renderer* g_renderer;
SDL_Window* g_window;
ED_Exit exit_event = 0;

void Init_EasyDraw(int screen_width, int screen_height, const char* title, ED_Exit atexit)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    TTF_Init();

    ED_Graphics::screen_width = screen_width;
    ED_Graphics::screen_height = screen_height;
    g_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        screen_width, screen_height, SDL_WINDOW_SHOWN);
    g_renderer = SDL_CreateRenderer(g_window, 0, SDL_RENDERER_TARGETTEXTURE);
    SDL_RenderClear(g_renderer);
    SDL_RenderPresent(g_renderer);

    exit_event = atexit;
    ED_Graphics::init();
}

void Final_EasyDraw()
{
    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}