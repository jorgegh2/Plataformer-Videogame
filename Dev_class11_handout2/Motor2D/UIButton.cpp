#include "UIButton.h"
#include "UIImage.h"
#include "UILabel.h"
#include "UIElement.h"
#include "j1Fonts.h"
#include "p2SString.h"
#include "j1App.h"
#include "j1Input.h"

UIButton::UIButton(iPoint position, SDL_Rect rectToDraw[], p2SString text, SDL_Color color, _TTF_Font* font, UIElement* parent, bool isEnabled) : UIElement(ButtonElement, position, parent, isEnabled)
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

	buttonLabel->CentralizeLabel(buttonImage);

}



UIButton::~UIButton()
{}

void UIButton::PreUpdate()
{
	
	buttonImage->PreUpdate();

}

void UIButton::Update(float dt)
{
	
	if (buttonImage->GetEvent() == MouseEnterEvent || buttonImage->GetEvent() == MouseLeftClickLeave)
	{
		buttonImage->setRectToDraw(rects[1]);
	}

	else if (buttonImage->GetEvent() == MouseLeaveEvent)
	{
		buttonImage->setRectToDraw(rects[0]);
	}

	else if (buttonImage->GetEvent() == MouseLeftClickEvent)
	{
		buttonImage->setRectToDraw(rects[2]);
	}


	
}

