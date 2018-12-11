#ifndef _UILABEL_H_
#define _UILABEL_H_

#include "UIElement.h"
#include "p2SString.h"

struct _TTF_Font;
struct SDL_Texture;

class UILabel : public UIElement
{
public:
	UILabel(iPoint position, p2SString text,  SDL_Color color,  _TTF_Font* font, UIElement* parent = nullptr);
	virtual ~UILabel();
	/*SDL_Rect default_texture_rect = { 0,0,0,0 };
	SDL_Rect mouse_on_rect = { 0,0,0,0 };
	SDL_Rect clicked_rect = { 0,0,0,0 };*/
	SDL_Texture* GetUITexture();
	SDL_Texture* textureFont; //
};

#endif

