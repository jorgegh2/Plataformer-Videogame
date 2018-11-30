#include "UIElement.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Input.h"


UIElement::UIElement(iPoint position, j1Module* listener, bool drag) : localPosition(position), listener(listener), dragable(drag)
{

}

UIElement::~UIElement()
{
	App->tex->UnLoad((SDL_Texture*)texture);
}

void UIElement::Update(float dt)
{
	//set the position for all childs
	

}

void UIElement::Draw()
{
	App->render->Blit(texture, positionUi.x, positionUi.y, &rectUi, SDL_FLIP_NONE, 0.0f);
}

void UIElement::DebugDraw() const
{
	SDL_Rect rect = { positionUi.x,positionUi.y,rectUi.w,rectUi.h };
	//App->render->DrawQuad(rect, 0, 0, 0, 100,false,false);
}

void UIElement::SetParent(UIElement* parent)
{
	this->parent = parent;
	positionToDraw = parent->positionToDraw + 1;
}

void UIElement::SetLocalPosition(iPoint p)
{
	localPosition.x = p.x;
	localPosition.y = p.y;
}

void UIElement::ChangeTexture(SDL_Texture* tex)
{
	if (texture != nullptr)
		App->tex->UnLoad((SDL_Texture*)texture);

	texture = tex;
}

void UIElement::ChangeTextureRect(SDL_Rect new_rect)
{
	rectUi = new_rect;
}

void UIElement::SetSliderButtonPos(int position) {}
