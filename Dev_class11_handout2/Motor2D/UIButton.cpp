#include "UIButton.h"
#include "UIImage.h"
#include "UILabel.h"
#include "UIElement.h"
#include "j1Fonts.h"
#include "p2SString.h"
#include "j1App.h"
#include "j1Input.h"

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

	//this->parent = parent;

	Event = NoEventElement;
}



UIButton::~UIButton()
{}

void UIButton::PreUpdate()
{
	

	switch (Event)
	{
	case NoEventElement:

		if (IsMouseInsideElement())
		{
			Event = MouseEnterEvent;
		}
		break;

	case MouseEnterEvent:

		buttonImage->setRectToDraw(rects[1]);
		
		Event = MouseInside;
		break;

	case MouseInside:

		if (!IsMouseInsideElement())
		{
			Event = MouseLeaveEvent;
		}
		else
		{
			if (App->input->GetMouseButtonDown(1) == KEY_DOWN)
			{
				Event = MouseLeftClickEvent;
			}
		}
		break;

	case MouseLeftClickEvent:
	
		buttonImage->setRectToDraw(rects[2]);
		
		Event = MouseLeftClickPressed;
		
		break;

	case MouseLeftClickPressed:

		if (App->input->GetMouseButtonDown(1) == KEY_UP)
		{
			//MouseEnterEvent to change the rect 
			Event = MouseEnterEvent;
		}

		break;

	case MouseLeaveEvent:

		buttonImage->setRectToDraw(rects[0]);
		Event = NoEventElement;
		break;

	}
}

void UIButton::Update(float dt)
{
	
	
	
}

bool UIButton::IsMouseInsideElement()
{
	SDL_Rect rectImage = buttonImage->GetRectToDraw();
	iPoint mousePosition;
	App->input->GetMousePosition(mousePosition.x, mousePosition.y);

	if (mousePosition.x > position.x && mousePosition.x < position.x + rectImage.w && mousePosition.y > position.y && mousePosition.y < position.y + rectImage.h)
		return true;
	else
		return false;
}