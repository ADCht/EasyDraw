#pragma once
#include "SDL.h"
#include "sprite.h"
#include "rect.h"
#include "graphics.h"
#include <vector>

class ED_Sprite;

class ED_Viewport
{
public:
	ED_Viewport();
	ED_Viewport(ED_Rect *rect_);
	ED_Viewport(int x_, int y_, int width_, int height_);
	~ED_Viewport();

	void dispose();
	bool IsDisposed();

	ED_Rect* rect;
	bool visible;
	int z;
	int ox;
	int oy;

	void add_sprite(ED_Sprite* sprite);
	void del_sprite(ED_Sprite* sprite);

public:
	void draw();

private:
	std::vector<ED_Sprite*> m_sprites;
	bool m_disposed;

};
