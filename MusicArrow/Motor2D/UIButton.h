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
	void Update(float dt);



private:
	UIImage * buttonImage = nullptr;
	UILabel* buttonLabel = nullptr;
	SDL_Rect rects[3];
	EventElement Event = NoEventElement;
	

};

#endif
