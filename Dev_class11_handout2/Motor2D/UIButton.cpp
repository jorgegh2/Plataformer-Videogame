#include "UIButton.h"
#include "UIImage.h"
#include "UILabel.h"
#include "UIElement.h"
#include "j1Fonts.h"
#include "p2SString.h"

UIButton::UIButton(iPoint position, SDL_Rect rectToDraw[], p2SString text, SDL_Color color, _TTF_Font* font, UIElement* parent) : UIElement(ButtonElement, position, parent)
{
	for (uint i = 0; i < 3; i++)
	{
		rects[i] = rectToDraw[i];
	}
	buttonImage = new UIImage(position, rectToDraw[0], this);
	listChildren.add(buttonImage);
	
	//funcion para centrar el texto y sacar su posicion relativa.
	buttonLabel = new UILabel(position, text, color, font, this);
	listChildren.add(buttonLabel);

	this->parent = parent;
}

UIButton::~UIButton()
{}

void UIButton::Update(float dt)
{
	buttonImage->setRectToDraw(rects[2]);
}