#include "j1App.h"
#include "UIElement.h"
#include "j1Render.h"
#include "p2Log.h"
#include "j1Textures.h"
#include "UIImage.h"
#include "j1Gui.h"

UIElement::UIElement(ElementType type, iPoint position, SDL_Rect rectToDraw)
{
	this->position = position;
	this->rectToDraw = rectToDraw;
	this->type = type;

}

UIElement::~UIElement()
{}

void UIElement::Draw(SDL_Texture* UItexture)
{
	//switch
	if (type == ImageElement ||type == LabelElement)
	{
		if (!App->render->Blit(UItexture, position.x, position.y, &rectToDraw))
		{
			LOG("ERROR to blit a Gui Entity!");
		}
	}
}

void UIElement::Update(float dt)
{
	
}

SDL_Texture* UIElement::GetUITexture()
{
	return App->gui->GetAtlas();
}