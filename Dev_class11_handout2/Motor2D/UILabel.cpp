#include "UILabel.h"
#include "j1App.h"
#include "j1Fonts.h"

UILabel::UILabel(iPoint position, p2SString text, SDL_Color color, _TTF_Font* font) : UIElement(position)
{
	type = LabelElement;
	App->font->CalcSize(text.GetString(), rectToDraw.w, rectToDraw.h, font);
	textureFont = App->font->Print(text.GetString(), color, font);
}