#include "UIButton.h"
#include "UIImage.h"
#include "UILabel.h"
#include "UIElement.h"
#include "j1Fonts.h"
#include "p2SString.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Scene.h"
#include "j1Audio.h"


UIButton::UIButton(iPoint position, SDL_Rect rectToDraw[], p2SString text, SDL_Color color, _TTF_Font* font, bool dragable, UIElement* parent, bool isEnabled) : UIElement(ButtonElement, position, parent, isEnabled, dragable, rectToDraw[0])
{
	for (uint i = 0; i < 3; i++)
	{
		rects[i] = rectToDraw[i];
	}

	buttonImage = new UIImage(position, rectToDraw[0], false, this);
	SetParentAndChildren(buttonImage);

	buttonLabel = new UILabel(position, text, color, font, false, this);
	SetParentAndChildren(buttonLabel);

	buttonLabel->CentralizeLabel(buttonImage);

}



UIButton::~UIButton()
{}

void UIButton::Update(float dt)
{
	
		if (GetEvent() == MouseLeftClickPressed && dragable == true)
		{
			DragUIElement();
		}

		if (GetEvent() == MouseEnterEvent)
		{
			buttonImage->setRectToDraw(rects[1]);
			App->audio->PlayFx(App->scene->audio_rollover);
		}

		else if (GetEvent() == MouseLeaveEvent)
		{
			buttonImage->setRectToDraw(rects[0]);
		}

		else if (GetEvent() == MouseLeftClickEvent)
		{
			buttonImage->setRectToDraw(rects[2]);
			App->audio->PlayFx(App->scene->audio_click);
		}
	
}



