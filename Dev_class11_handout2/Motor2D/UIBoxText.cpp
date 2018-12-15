#include "UIBoxText.h"
#include "UIElement.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Fonts.h"

UIBoxText::UIBoxText(iPoint position, SDL_Rect rectImage, p2SString text, SDL_Color color, _TTF_Font* font, bool dragable, UIElement* parent, bool isEnabled) : UIElement(BoxTextElement, position, parent, isEnabled, dragable, rectImage)
{
	BoxTextImage = new UIImage(position, rectImage, dragable, this);
	listChildren.add(BoxTextImage);

	//funcion para centrar el texto y sacar su posicion relativa.
	BoxTextLabelInitial = new UILabel(position, text, color, font,false, this);
	listChildren.add(BoxTextLabelInitial);
	BoxTextLabelInitial->InitPosToWrite(BoxTextImage);

	BoxTextLabel = new UILabel(position, "", color, font, false, this, false);
	listChildren.add(BoxTextLabel);
	BoxTextLabel->InitPosToWrite(BoxTextImage);


	finalRect.x = position.x + MARGIN;
	finalRect.y = BoxTextLabelInitial->GetPosition().y;
	finalRect.w = QUAD_WIDTH;
	finalRect.h = BoxTextLabelInitial->GetRectToDraw().h;

	timer.Start();

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
	if(Event == MouseLeftClickPressed && dragable == true)
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
				BoxTextLabelInitial->isEnabled = true;
				BoxTextLabel->isEnabled = false;
			}
		}
		break;

	case MouseLeftClickEvent:
		BoxTextLabelInitial->isEnabled = false;
		BoxTextLabel->isEnabled = true;
	
		break;

	case MouseLeftClickPressed:
		if (dragable == true)
		{
			DragUIElement();
		}
		break;
	}

	if (!BoxTextLabelInitial->isEnabled)//BoxTextLabel is enabled
	{
		if (timer.ReadSec() >= 0.5f)
		{
			printFinalQuad(finalRect);
			if (timer.ReadSec() >= 1.0f)
			{
				timer.Start();
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
