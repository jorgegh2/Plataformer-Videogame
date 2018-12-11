#ifndef _UIBUTTON_
#define _UIBUTTON_

#include "UIElement.h"

class UIImage;
class UILabel;

class UIButton : public UIElement
{
public:
	UIButton(iPoint, SDL_Rect[], bool);
	//SDL_Rect default_texture_rect = { 0,0,0,0 };
	//SDL_Rect mouse_on_rect = { 0,0,0,0 };
	//SDL_Rect clicked_rect = { 0,0,0,0 };
private:
	UIImage* buttonImage;
	UILabel* buttonLabel;
};

#endif
