#ifndef _UIBUTTON_
#define _UIBUTTON_

#include "UIElement.h"
//#include "p2SString.h"

class UIImage;
class UILabel;
struct _TTF_Font;
class p2SString;
struct SDL_Texture;


class UIButton : public UIElement
{
public:
	UIButton(iPoint, SDL_Rect[], p2SString text, SDL_Color color, _TTF_Font* font, bool dragable, UIElement* parent = nullptr, bool isEnabled = true);
	virtual ~UIButton();
	//void PreUpdate();
	void Update(float dt);
	

	//SDL_Rect default_texture_rect = { 0,0,0,0 };
	//SDL_Rect mouse_on_rect = { 0,0,0,0 };
	//SDL_Rect clicked_rect = { 0,0,0,0 };
private:
	UIImage* buttonImage;
	UILabel* buttonLabel;
	SDL_Rect rects[3];
	EventElement Event = NoEventElement;
};

#endif
