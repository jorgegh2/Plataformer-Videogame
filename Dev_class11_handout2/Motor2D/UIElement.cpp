#include "j1App.h"
#include "UIElement.h"
#include "j1Render.h"
#include "p2Log.h"
#include "j1Textures.h"
#include "UIImage.h"
#include "j1Gui.h"
#include "j1Input.h"

UIElement::UIElement(ElementType type, iPoint position, UIElement* parent, bool isEnabled, SDL_Rect rectToDraw, bool dragable)
{
	this->position = position;
	this->rectToDraw = rectToDraw;
	this->type = type;
	this->parent = parent;
	this->isEnabled = isEnabled;
	this->dragable = dragable;
}

//UIElement::UIElement(ElementType type, iPoint position, bool isEnabled)
//{
//	this->position = position;
//	this->rectToDraw = rectToDraw;
//	this->type = type;
//}

UIElement::~UIElement()
{}

void UIElement::Draw(SDL_Texture* UItexture)
{
	if (!App->render->Blit(UItexture, position.x, position.y, &rectToDraw))
	{
		LOG("ERROR to blit a Gui Entity!");
	}


	for (p2List_item<UIElement*>* item = listChildren.start; item; item = item->next)
	{
		if (item->data->isEnabled)
		{
			item->data->Draw(item->data->GetUITexture());
		}
	}
}

void UIElement::PreUpdate()
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

		Event = MouseLeftClickPressed;

		break;

	case MouseLeftClickPressed:

		if (App->input->GetMouseButtonDown(1) == KEY_UP)
		{
			//MouseEnterEvent to change the rect 
			Event = MouseLeftClickLeave;
		}

		break;

	case MouseLeftClickLeave:

		Event = MouseInside;
		break;

	case MouseLeaveEvent:

		Event = NoEventElement;
		break;

	}
}

void UIElement::Update(float dt)
{
	
}



SDL_Texture* UIElement::GetUITexture()
{
	return App->gui->GetAtlas();
}

UIElement* UIElement::GetParent() const
{
	return parent;
}

SDL_Rect UIElement::GetRectToDraw() const
{
	return rectToDraw;
}

iPoint UIElement::GetPosition() const
{
	return position;
}


bool UIElement::IsMouseInsideElement()
{
	//SDL_Rect rectImage = buttonImage->GetRectToDraw();
	iPoint mousePosition;
	App->input->GetMousePosition(mousePosition.x, mousePosition.y);

	if (mousePosition.x > position.x && mousePosition.x < position.x + rectToDraw.w && mousePosition.y > position.y && mousePosition.y < position.y + rectToDraw.h)
		return true;
	else
		return false;
}

void UIElement::DragUIElement()
{
	iPoint mousePosition;
	App->input->GetMousePosition(mousePosition.x, mousePosition.y);

	position = mousePosition;
}

EventElement UIElement::GetEvent() const
{
	return Event;
}