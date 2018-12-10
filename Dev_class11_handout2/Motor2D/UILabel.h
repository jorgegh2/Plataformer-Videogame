#ifndef _UILABEL_H_
#define _UILABEL_H_

#include "UIElement.h"
#include "p2SString.h"

struct _TTF_Font;

class UILabel : public UIElement
{
public:
	UILabel(iPoint position, p2SString text, SDL_Color color, _TTF_Font* font);
	/*SDL_Rect default_texture_rect = { 0,0,0,0 };
	SDL_Rect mouse_on_rect = { 0,0,0,0 };
	SDL_Rect clicked_rect = { 0,0,0,0 };*/
};

#endif

