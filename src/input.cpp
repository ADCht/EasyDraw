#include "input.h"

std::vector<int> ED_Input::status(20);
std::vector<int> ED_Input::key_timer(20);

static ED_InputKeys get_key_id(SDL_Keycode code)
{
    static ED_InputKeys ret;
    switch (code)
    {
    case SDLK_DOWN:
        ret = DOWN;
        break;
    case SDLK_LEFT:
        ret = LEFT;
        break;
    case SDLK_RIGHT:
        ret = RIGHT;
        break;
    case SDLK_UP:
        ret = UP;
        break;

    case SDLK_LSHIFT:
        ret = A;
        break;
    case SDLK_RSHIFT:
        ret = A;
        break;

    case SDLK_x:
        ret = B;
        break;
    case SDLK_ESCAPE:
        ret = B;
        break;

    case SDLK_z:
        ret = C;
        break;
    case SDLK_SPACE:
        ret = C;
        break;

    case SDLK_a:
        ret = X;
        break;

    case SDLK_s:
        ret = Y;
        break;

    case SDLK_d:
        ret = Z;
        break;

    case SDLK_q:
        ret = L;
        break;

    case SDLK_w:
        ret = R;
        break;

    default:
        ret = NONE;
        break;
    }
    return ret;
}

void ED_Input::update()
{
    SDL_Event s_event;
    SDL_PollEvent(&s_event);
    if (s_event.type == SDL_QUIT)
    {
        Final_EasyDraw();
        exit_event();
        exit(-1);
    }
    if (s_event.type == SDL_KEYDOWN || s_event.type == SDL_KEYUP)
    {
        int id = get_key_id(s_event.key.keysym.sym);
        if (s_event.key.state == SDL_PRESSED)
        {
            if (key_timer[id] > 10)
            {
                status[id] = 3;
            }
            else {
                if (status[id] >= 1) // Repeat
                {
                    status[id] = 2;
                    key_timer[id] += 1;
                }
                else if(status[id] == 0)
                {
                    status[id] = 1; // Trigger
                    key_timer[id] += 1;
                }
            }
            return;
        }
        if (s_event.key.state == SDL_RELEASED)
        {
            status[id] = 0;
            key_timer[id] = 0;
            return;
        }
    }
}

bool ED_Input::IsPressed(int key)
{
    if (key < 0 || key > 20) return false;
	return status[key] > 0;
}

bool ED_Input::IsTriggered(int key)
{
    if (key < 0 || key > 20) return false;
	return status[key] == 1;
}

bool ED_Input::IsRepeated(int key)
{
    if (key < 0 || key > 20) return false;
    return status[key] > 2;
}
