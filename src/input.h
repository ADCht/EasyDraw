#pragma once
#include "SDL.h"
#include "ed_main.h"
#include <vector>

namespace ED_Input
{
	extern std::vector<int> status;
    extern std::vector<int> key_timer;

	void update();

	bool IsPressed(int key);
	bool IsTriggered(int key);
	bool IsRepeated(int key);
}

enum ED_InputKeys {
    NONE = -1,
    // Your Arrow Keys.
    DOWN = 0,
    LEFT,
    RIGHT,
    UP,
    // Your Normal Keys.
    A,
    B,
    C,
    X,
    Y,
    Z,
    L,
    R,
    // Your Special Keys.
    SHIFT,
    CTRL,
    ALT,
    // Your FFF Keys.
    F5,
    F6,
    F7,
    F8,
    F9
};
