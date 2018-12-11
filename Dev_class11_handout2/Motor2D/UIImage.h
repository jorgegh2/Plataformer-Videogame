#ifndef _UIIMAGE_H_
#define _UIIMAGE_H_

#include "UIElement.h"
class UIImage : public UIElement
{
public:
	UIImage(iPoint, SDL_Rect, UIElement* parent = nullptr);
	virtual ~UIImage();
	void setRectToDraw(SDL_Rect newRectToDraw);
	/*SDL_Rect default_texture_rect = { 0,0,0,0 };
	SDL_Rect mouse_on_rect = { 0,0,0,0 };
	SDL_Rect clicked_rect = { 0,0,0,0 };*/
};

#endif