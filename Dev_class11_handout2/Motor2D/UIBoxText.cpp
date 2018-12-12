#include "UIBoxText.h"
#include "UIElement.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1Input.h"

UIBoxText::UIBoxText(iPoint position, SDL_Rect rectImage, p2SString text, SDL_Color color, _TTF_Font* font, UIElement* parent, bool isEnabled) : UIElement(BoxTextElement, position, parent, isEnabled)
{
	BoxTextImage = new UIImage(position, rectImage, this);
	listChildren.add(BoxTextImage);

	//funcion para centrar el texto y sacar su posicion relativa.
	BoxTextLabelInitial = new UILabel(position, text, color, font, this);
	listChildren.add(BoxTextLabelInitial);
	BoxTextLabelInitial->InitPosToWrite(BoxTextImage);

	BoxTextLabel = new UILabel(position, text, color, font, this, false);
	listChildren.add(BoxTextLabel);
	BoxTextLabel->InitPosToWrite(BoxTextImage);


	finalRect.x = position.x + MARGIN;
	finalRect.y = BoxTextLabelInitial->GetPosition().y;
	finalRect.w = QUAD_WIDTH;
	finalRect.h = BoxTextLabelInitial->GetRectToDraw().h;
}

UIBoxText::~UIBoxText()
{

}

void UIBoxText::printFinalQuad(SDL_Rect finalRect)
{
	App->render->DrawQuad(finalRect, 255, 255, 255, 255);
}

void UIBoxText::PreUpdate()
{
	switch (Event)
	{
	case NoEventElement:

		if (BoxTextLabelInitial->IsMouseInsideElement())
		{
			Event = MouseInside;
		}
		break;

	case MouseInside:
		if (!BoxTextLabelInitial->IsMouseInsideElement())
		{
			Event = NoEventElement;
		}
		else
		{
			if (App->input->GetMouseButtonDown(1) == KEY_DOWN)
			{
				Event = MouseLeftClickEvent;
				BoxTextLabelInitial->isEnabled = false;
				//BoxTextLabel->isEnabled = true;
			}
		}
		break;

	case MouseLeftClickEvent:
		
		if (!BoxTextLabelInitial->IsMouseInsideElement())
		{
			if (App->input->GetMouseButtonDown(1) == KEY_DOWN)
			{
				Event = NoEventElement;
				BoxTextLabelInitial->isEnabled = true;
				//BoxTextLabel->isEnabled = false;
			}
		}
		break;
		
	/*case MouseLeaveEvent:
		break;*/
	}
}

void UIBoxText::Update(float dt)
{
	if (Event == MouseLeftClickEvent)
	{
		printFinalQuad(finalRect);
	}
}
