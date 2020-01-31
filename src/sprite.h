#pragma once
#include "SDL.h"
#include "viewport.h"
#include "bitmap.h"
#include "graphics.h"
#include "tone.h"

class ED_Viewport;

class ED_Sprite
{
public:
	ED_Sprite();
	ED_Sprite(ED_Viewport *viewport_);
	~ED_Sprite();

	ED_Viewport* get_viewport();
	void set_viewport(ED_Viewport* viewport_);
	void set_bitmap(ED_Bitmap* bitmap_);
	ED_Bitmap* get_bitmap();

	ED_Rect* src_rect;
	bool visible;
	int x;
	int y;
	int z;
	int ox;
	int oy;
	double zoom_x;
	double zoom_y;
	int angle;
	bool mirror;
	bool vertical;
	int opacity;
	int blend_type;
	ED_Color *color;
	ED_Tone *tone;

private:
	ED_Viewport* viewport;
	ED_Bitmap* bitmap;

public:
	void draw();

};