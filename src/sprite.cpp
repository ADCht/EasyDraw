#include "sprite.h"
#include "SDL2_rotozoom.h"

ED_Sprite::ED_Sprite()
{
	this->viewport = new ED_Viewport();
	this->bitmap = 0;
	this->src_rect = 0;
	this->visible = true;
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->ox = 0;
	this->oy = 0;
	this->zoom_x = 1;
	this->zoom_y = 1;
	this->angle = 0;
	this->opacity = 255;
	this->blend_type = 0;
	this->tone = 0;
	this->color = 0;
	this->mirror = false;
	this->viewport->add_sprite(this);
}

ED_Sprite::ED_Sprite(ED_Viewport* viewport_)
{
	this->viewport = viewport_;
	this->bitmap = 0;
	this->src_rect = 0;
	this->visible = true;
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->ox = 0;
	this->oy = 0;
	this->zoom_x = 1;
	this->zoom_y = 1;
	this->angle = 0;
	this->opacity = 255;
	this->blend_type = 0;
	this->tone = 0;
	this->color = 0;
	this->mirror = false;
	this->viewport->add_sprite(this);
}

ED_Sprite::~ED_Sprite()
{
	this->viewport->del_sprite(this);
	this->viewport = 0;
	this->bitmap = 0;
	this->src_rect = 0;
	this->visible = false;
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->ox = 0;
	this->oy = 0;
	this->zoom_x = 1;
	this->zoom_y = 1;
	this->angle = 0;
	this->opacity = 255;
	this->tone = new ED_Tone();
	this->color = new ED_Color();
	this->blend_type = 0;
	this->mirror = false;
}

ED_Viewport* ED_Sprite::get_viewport()
{
	return this->viewport;
}

void ED_Sprite::set_viewport(ED_Viewport* viewport_)
{
	if (viewport_ = 0) // dispose viewport
	{
		this->viewport->del_sprite(this);
		this->viewport = 0;
	}
	else 
	{
		this->viewport->del_sprite(this);
		this->viewport = viewport_;
		this->viewport->add_sprite(this);
	}
}

void ED_Sprite::set_bitmap(ED_Bitmap* bitmap_)
{
	this->bitmap = bitmap_;
	this->src_rect = bitmap_->rect();
}

ED_Bitmap* ED_Sprite::get_bitmap()
{
	return this->bitmap;
}

static void set_surface_mirror(SDL_Surface *surface)
{
	unsigned char* pixels = (unsigned char*)surface->pixels;
	unsigned char* new_bitmap = new unsigned char[surface->w * surface->h * 4];
	int temp = 0;
	int height_add = 0;
	for (int y1 = 0; y1 < surface->h; y1++) {
		for (int x1 = 1; x1 <= surface->w; x1++) {
			temp = surface->w - x1 + 1;
			height_add = y1 * (surface->w * 4);
			//std::swap(pixels[x1 * 4 - 4 + height_add], pixels[temp * 4 - 4 + height_add]);
			//std::swap(pixels[x1 * 4 - 3 + height_add], pixels[temp * 4 - 3 + height_add]);
			//std::swap(pixels[x1 * 4 - 2 + height_add], pixels[temp * 4 - 2 + height_add]);
			//std::swap(pixels[x1 * 4 - 1 + height_add], pixels[temp * 4 - 1 + height_add]);
			new_bitmap[x1 * 4 - 4 + height_add] = pixels[temp * 4 - 4 + height_add]; // red
			new_bitmap[x1 * 4 - 3 + height_add] = pixels[temp * 4 - 3 + height_add]; // green
			new_bitmap[x1 * 4 - 2 + height_add] = pixels[temp * 4 - 2 + height_add]; // blue
			new_bitmap[x1 * 4 - 1 + height_add] = pixels[temp * 4 - 1 + height_add]; // alpha
		}
	}
	surface->pixels = new_bitmap;
}

void ED_Sprite::draw()
{
	if (!this->visible) return;
	if (!this->bitmap) return;

	int base_x = 0, base_y = 0;
	base_x = this->x - this->ox;
	base_y = this->y - this->oy;

	if (this->viewport)
	{
		SDL_SetClipRect(ED_Graphics::canvas, this->viewport->rect->entity());
		base_x += this->viewport->rect->x - this->viewport->ox;
		base_x += this->viewport->rect->y - this->viewport->oy;
	}

	SDL_Rect dst_rect;
	dst_rect.x = base_x;
	dst_rect.y = base_y;
	dst_rect.w = this->src_rect->width;
	dst_rect.h = this->src_rect->height;

	SDL_Surface* pNew = rotozoomSurfaceXY(this->bitmap->entity(), this->angle, this->zoom_x, this->zoom_y, SMOOTHING_ON);

	SDL_Rect src_rect;
	src_rect.x = 0;
	src_rect.y = 0;
	src_rect.w = pNew->w;
	src_rect.h = pNew->h;

	switch (this->blend_type)
	{
	case 1:
		SDL_SetSurfaceBlendMode(pNew, SDL_BLENDMODE_ADD);
		break;
	case 2:
		SDL_SetSurfaceBlendMode(pNew, SDL_BLENDMODE_BLEND);
		break;
	default:
		break;
	}

	if (this->tone)
		SDL_SetSurfaceColorMod(pNew, this->tone->red, this->tone->green, this->tone->blue);
	SDL_SetSurfaceAlphaMod(pNew, this->opacity);

	if (this->mirror)
		set_surface_mirror(pNew); // sprite mirror

	SDL_BlitSurface(pNew, &src_rect, ED_Graphics::canvas, &dst_rect);

	SDL_FreeSurface(pNew);
	
	if (this->viewport)
		SDL_SetClipRect(ED_Graphics::canvas, 0);
}
