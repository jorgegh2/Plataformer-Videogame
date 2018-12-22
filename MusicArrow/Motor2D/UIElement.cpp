#include "j1App.h"
#include "UIElement.h"
#include "j1Render.h"
#include "p2Log.h"
#include "j1Textures.h"
#include "UIImage.h"
#include "j1Gui.h"
#include "j1Input.h"

UIElement::UIElement(ElementType type, iPoint position, UIElement* parent, bool isEnabled, bool dragable, SDL_Rect rectToDraw)
{
	this->position = position;
	this->rectToDraw = rectToDraw;
	this->type = type;
	//	this->parent = parent;
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
	if (type != ButtonElement && type != BoxTextElement && type != SliderElement && UItexture != nullptr)  // only blit their children. Button, boxText ans Slider don't have anything to blit.
	{
		if (!App->render->Blit(UItexture, position.x, position.y, &rectToDraw))
		{
			LOG("ERROR to blit a Gui Entity!");
		}
	}


	for (p2List_item<UIElement*>* item = listChildren.start; item; item = item->next)
	{
		if (item->data->isEnabled)
		{
			item->data->Draw(item->data->GetUITexture());
		}
	}

	if (disabled)
	{
		App->render->DrawQuad({ position.x, position.y, rectToDraw.w, rectToDraw.h }, 0, 0, 0, 80);
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
		mousePositionFirst = { 0,0 };
		if (dragable == true)
		{
			App->input->GetMousePosition(mousePositionFirst.x, mousePositionFirst.y);
		}

		break;

	case MouseLeftClickPressed:

		if (App->input->GetMouseButtonDown(1) == KEY_UP)
		{
			Event = MouseLeftClickLeave;
		}

		break;

	case MouseLeftClickLeave:

		Event = MouseInside;
		mousePositionFinal = { 0,0 };
		break;

	case MouseLeaveEvent:

		Event = NoEventElement;
		break;

	}
}

void UIElement::Update(float dt)
{
	if (Event == MouseLeftClickPressed && dragable == true)
	{
		DragUIElement();
	}
}



SDL_Texture* UIElement::GetUITexture()
{
	return App->gui->GetAtlas();
}

UIElement* UIElement::GetParent() const
{
	return parent;
}

SDL_Rect UIElement::GetRectToDraw()
{
	return rectToDraw;
}

iPoint UIElement::GetPosition() const
{
	return position;
}


bool UIElement::IsMouseInsideElement(int marginX, int marginY)
{
	iPoint mousePosition;
	App->input->GetMousePosition(mousePosition.x, mousePosition.y);

	if (mousePosition.x > position.x - marginX && mousePosition.x < position.x + rectToDraw.w + marginX && mousePosition.y > position.y - marginY && mousePosition.y < position.y + rectToDraw.h + marginY)
		return true;
	else
		return false;
}

void UIElement::DragUIElement()
{
	App->input->GetMousePosition(mousePositionFinal.x, mousePositionFinal.y);
	iPoint movement = mousePositionFinal - mousePositionFirst;
	if (parent == nullptr)
	{
		position += movement;
	}
	else
	{
		if (parent->type != SliderElement)
		{

			MoveInParentLimits(movement.x, movement.y);
		}
		else
		{
			int margin = MARGIN;
			if (parent->IsMouseInsideElement(margin))
			{
				if (posX != -1 && parent->horizontalSlider == true)
				{
					position.x = posX;
					posX = -1;
				}
				if (posY != -1 && parent->horizontalSlider == false)
				{
					position.y = posY;
					posY = -1;
				}

				MoveInParentLimits(movement.x, movement.y);
			}
			else
			{
				App->input->GetMousePosition(posX, posY);
			}
		}
	}
	for (p2List_item<UIElement*>* item = listChildren.start; item; item = item->next)
	{
		item->data->position += movement;
	}

	mousePositionFirst = mousePositionFinal;
}

EventElement UIElement::GetEvent() const
{
	return Event;
}

void UIElement::SetParentAndChildren(UIElement* children)
{
	listChildren.add(children);
	children->parent = this;
}

void UIElement::MoveInParentLimits(int movementX, int movementY)
{
	int newPosX = position.x + movementX;
	if (newPosX > parent->GetPosition().x && newPosX + rectToDraw.w < parent->GetPosition().x + parent->GetRectToDraw().w)
	{
		position.x = newPosX;
	}
	int newPosY = position.y + movementY;
	if (newPosY > parent->GetPosition().y && newPosY + rectToDraw.h < parent->GetPosition().y + parent->GetRectToDraw().h)
	{
		position.y = newPosY;
	}

}

void UIElement::ChangeEnabled()
{
	isEnabled = !isEnabled;

	for (p2List_item<UIElement*>* item = listChildren.start; item; item = item->next)
	{
		item->data->isEnabled = !item->data->isEnabled;
	}

}
