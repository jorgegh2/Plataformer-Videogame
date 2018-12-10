#include "UILabel.h"
#include "j1App.h"
#include "j1Fonts.h"
#include "j1Textures.h"
#include "p2Log.h"

UILabel::UILabel(iPoint position, p2SString text, SDL_Color color, _TTF_Font* font) : UIElement(LabelElement, position)
{
	App->font->CalcSize(text.GetString(), rectToDraw.w, rectToDraw.h, font);
	textureFont = App->font->Print(text.GetString(), color, font);
}

UILabel::~UILabel()
{
	if (!App->tex->UnLoad(textureFont))
	{
		LOG("ERROR to Unload textureFont");
	}
}

SDL_Texture* UILabel::GetUITexture()
{
	return textureFont;
}