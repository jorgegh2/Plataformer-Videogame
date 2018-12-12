#ifndef _UIBOXTEXT_H_
#define _UIBOXTEXT_H_

#include "UIElement.h"
#include "UIImage.h"
#include "UILabel.h"

class UIBoxText : public UIElement
{
public:
	UIBoxText(iPoint position, SDL_Rect rectImage, p2SString text, SDL_Color color, _TTF_Font* font, UIElement* parent = nullptr);
	virtual ~UIBoxText();
	void printFinalQuad(SDL_Rect finalRect);
	void Update(float dt);
	
	
private:
	UIImage* BoxTextImage;
	UILabel* BoxTextLabelInitial;
	UILabel* BoxTextLabel;
	SDL_Rect finalRect;
};

#endif
