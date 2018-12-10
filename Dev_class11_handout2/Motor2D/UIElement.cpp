#include "j1App.h"
#include "UIElement.h"
#include "j1Render.h"
#include "p2Log.h"
#include "j1Textures.h"
#include "UIImage.h"

UIElement::UIElement(iPoint position, SDL_Rect rectToDraw)
{
	this->position = position;
	this->rectToDraw = rectToDraw;

}

UIElement::~UIElement()
{}

void UIElement::Draw(SDL_Texture* atlas)
{
	//switch
	if (type == ImageElement)
	{
		if (!App->render->Blit(atlas, position.x, position.y, &rectToDraw))
		{
			LOG("ERROR to blit a Gui Entity!");
		}
	}

	if (type == LabelElement)
	{
		if (!App->render->Blit(textureFont, position.x, position.y, &rectToDraw))
		{
			LOG("ERROR to blit a Gui Entity!");
		}
	}

}

void UIElement::Update(float dt)
{
	
}