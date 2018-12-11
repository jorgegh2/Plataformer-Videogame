#include "UIButton.h"
#include "UIImage.h"
#include "UILabel.h"
#include "UIElement.h"
#include "j1Fonts.h"
#include "p2SString.h"

UIButton::UIButton(iPoint position, SDL_Rect rectToDraw[], p2SString text, SDL_Color color, _TTF_Font* font, UIElement* parent) : UIElement(ButtonElement, position, parent)
{
	buttonImage = new UIImage(position, rectToDraw[0], this);
	listChildren.add(buttonImage);

	buttonLabel = new UILabel(position, text, color, font, this);
	listChildren.add(buttonLabel);

	this->parent = parent;
}

UIButton::~UIButton()
{}