#ifndef _UIBUTTON_
#define _UIBUTTON_

#include "UIElement.h"

class UIButton : public UIElement
{
public:
	//UIButton(iPoint, SDL_Rect, SDL_Rect, SDL_Rect, ElementType, bool);
	SDL_Rect default_texture_rect = { 0,0,0,0 };
	SDL_Rect mouse_on_rect = { 0,0,0,0 };
	SDL_Rect clicked_rect = { 0,0,0,0 };
};

#endif
