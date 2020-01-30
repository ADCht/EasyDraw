#include "ed_main.h"
#include "SDL_opengl.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "SDL_mixer.h"

SDL_Renderer* g_renderer;
SDL_Window* g_window;

void Init_EasyDraw(int screen_width, int screen_height)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    Mix_Init(MIX_INIT_MP3 | MIX_INIT_MID | MIX_INIT_OGG | MIX_INIT_FLAC);
    TTF_Init();

    ED_Graphics::screen_width = screen_width;
    ED_Graphics::screen_height = screen_height;
    g_window = SDL_CreateWindow("SDLGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        screen_width, screen_height, SDL_WINDOW_SHOWN);
    SDL_SetWindowResizable(g_window, SDL_TRUE);
    g_renderer = SDL_CreateRenderer(g_window, 0, SDL_RENDERER_TARGETTEXTURE);

    ED_Graphics::init();

    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1536);
}

void Final_EasyDraw()
{
    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);
    Mix_CloseAudio();

    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}