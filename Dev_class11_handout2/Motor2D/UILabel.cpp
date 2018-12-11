#include "UILabel.h"
#include "j1App.h"
#include "j1Fonts.h"
#include "j1Textures.h"

UILabel::UILabel(iPoint position, p2SString text, SDL_Color color, _TTF_Font* font, UIElement* parent) : UIElement(LabelElement, position, parent)
{
	App->font->CalcSize(text.GetString(), rectToDraw.w, rectToDraw.h, font);
	textureFont = App->font->Print(text.GetString(), color, font);
}

UILabel::~UILabel()
{
	App->tex->UnLoad(textureFont);
}

SDL_Texture* UILabel::GetUITexture()
{
	return textureFont;
}