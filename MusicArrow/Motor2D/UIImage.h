#ifndef _UIIMAGE_H_
#define _UIIMAGE_H_

#include "UIElement.h"
class UIImage : public UIElement
{
public:
	UIImage(iPoint, SDL_Rect, bool dragable, UIElement* parent = nullptr, bool isEnabled = true);
	virtual ~UIImage();
	void setRectToDraw(SDL_Rect newRectToDraw);

};

#endif
