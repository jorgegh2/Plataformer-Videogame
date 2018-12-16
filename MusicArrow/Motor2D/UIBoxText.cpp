#include "UIBoxText.h"
#include "UIElement.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Fonts.h"

UIBoxText::UIBoxText(iPoint position, SDL_Rect rectImage, p2SString text, SDL_Color color, _TTF_Font* font, bool dragable, UIElement* parent, bool isEnabled) : UIElement(BoxTextElement, position, parent, isEnabled, dragable, rectImage)
{
	BoxTextImage = new UIImage(position, rectImage, false, this);
	SetParentAndChildren(BoxTextImage);

	//funcion para centrar el texto y sacar su posicion relativa.
	BoxTextLabelInitial = new UILabel(position, text, color, font, false, this);
	SetParentAndChildren(BoxTextLabelInitial);
	BoxTextLabelInitial->InitPosToWrite(BoxTextImage);

	BoxTextLabel = new UILabel(position, "", color, font, false, this, false);
	SetParentAndChildren(BoxTextLabel);
	BoxTextLabel->InitPosToWrite(BoxTextImage);


	finalRect.x = position.x + MARGIN;
	finalRect.y = BoxTextLabelInitial->GetPosition().y;
	finalRect.w = QUAD_WIDTH;
	finalRect.h = BoxTextLabelInitial->GetRectToDraw().h;

	timer.Reset();

	SDL_StartTextInput();
}

UIBoxText::~UIBoxText()
{
	SDL_StopTextInput();
}

void UIBoxText::printFinalQuad(SDL_Rect& finalRect)
{
	finalRect.x = BoxTextLabel->GetPosition().x + BoxTextLabel->GetRectToDraw().w;
	finalRect.y = BoxTextLabel->GetPosition().y;
	App->render->DrawQuad(finalRect, 255, 255, 255, 255);
}

//void UIBoxText::PreUpdate()
//{
//	BoxTextLabelInitial->PreUpdate();
//}

void UIBoxText::Update(float dt)
{
	if (Event == MouseLeftClickPressed && dragable == true)
	{
		DragUIElement();
	}
	switch (GetEvent())
	{
	case NoEventElement:

		if (App->input->GetMouseButtonDown(1) == KEY_DOWN)
		{
			if (!BoxTextLabelInitial->isEnabled)
			{
				focusQuad = false;
				if (BoxTextLabel->text == "")
				{
					BoxTextLabelInitial->isEnabled = true;
					BoxTextLabel->isEnabled = false;
				}
			}
		}
		break;

	case MouseLeftClickEvent:
		BoxTextLabelInitial->isEnabled = false;
		BoxTextLabel->isEnabled = true;
		focusQuad = true;

		break;

	case MouseLeftClickPressed:
		if (dragable == true)
		{
			DragUIElement();
		}
		break;
	}

	if (focusQuad)//BoxTextLabel is enabled
	{
		if (timer.ReadSec() >= 0.5f)
		{
			printFinalQuad(finalRect);
			if (timer.ReadSec() >= 1.0f)
			{
				timer.Reset();
			}

		}

		if (App->input->GetNewCharacterDetected())
		{
			EditBoxTextLabel(App->input->GetNewCharacter());
			App->input->ChangeBoolCharacterDetected();
		}

		if (App->input->GetKey(SDL_SCANCODE_BACKSPACE) == KEY_DOWN)
		{
			BoxTextLabel->text.Cut(BoxTextLabel->text.Length() - 1);
			BoxTextLabel->SetNewSizeAndTextureFont(BoxTextLabel->text);
		}

	}

}

void UIBoxText::EditBoxTextLabel(p2SString newCharacter)
{
	BoxTextLabel->text += newCharacter;
	BoxTextLabel->SetNewSizeAndTextureFont(BoxTextLabel->text);

}
