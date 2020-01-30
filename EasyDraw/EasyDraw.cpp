// EasyDraw.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL2_rotozoom.h"
#include "..\src\bitmap.h"
#include "..\src\ed_main.h"
#include "..\src\audio.h"

#include "SDL_main.h"

int main(int argc, char* argv[])
{
    Init_EasyDraw();

    char filename[1024];
    std::cout << "FileName:\n";
    std::cin >> filename;

    ED_Bitmap* bmp = new ED_Bitmap(filename);

    char a_filename[1024];
    std::cout << "AudioFileName:\n";
    std::cin >> a_filename;

    ED_Audio::bgm_play(a_filename);

    bmp->clear_rect(10, 10, 10, 10);

    ED_Color* cr = new ED_Color(255, 255, 255);
    bmp->set_pixel(15, 15, cr);

    std::cout << bmp->get_pixel(12, 12)->red;

    ED_Font* font = new ED_Font("font.ttf", 24);
    bmp->m_font = font;
    bmp->draw_text(25, 25, 544, 416, "Test Text", 1); // 居中

    SDL_Surface* pBitmap = bmp->entity();

    bool quit = false;
    SDL_Event event;
    double angle = 0;
    while (!quit)
    {
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                quit = true;
                break;
            }
        }
        SDL_RenderClear(g_renderer);

        // 刷新
        SDL_Surface* pNew = rotozoomSurface(pBitmap, angle, 1, SMOOTHING_ON);

        SDL_Texture* pTexture = SDL_CreateTextureFromSurface(g_renderer, pNew);
        SDL_RenderCopy(g_renderer, pTexture, NULL, NULL);
        SDL_DestroyTexture(pTexture);
        SDL_FreeSurface(pNew);

        SDL_RenderPresent(g_renderer);
        SDL_Delay(1000 / 60);

        angle += 1;
        if (angle > 360)
            angle = 0;
    }

    Final_EasyDraw();
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
