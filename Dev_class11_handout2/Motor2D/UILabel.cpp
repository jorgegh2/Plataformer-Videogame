#include "UILabel.h"
#include "j1App.h"
#include "j1Fonts.h"
#include "j1Textures.h"
#include "UIImage.h"
#include "p2Point.h"

UILabel::UILabel(iPoint position, p2SString text, SDL_Color color, _TTF_Font* font, bool dragable, UIElement* parent, bool isEnabled) : UIElement(LabelElement, position, parent, isEnabled, dragable)
{
	App->font->CalcSize(text.GetString(), rectToDraw.w, rectToDraw.h, font);
	this->text = text;
	this->color = color;
	this->font = font;
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

void UILabel::CentralizeLabel(UIImage* image)
{
	iPoint midPosLabel;
	iPoint midPosImage;

	midPosLabel = { position.x + (rectToDraw.w / 2), position.y + (rectToDraw.h / 2) };
	midPosImage = { image->GetPosition().x + (image->GetRectToDraw().w / 2), image->GetPosition().y + (image->GetRectToDraw().h / 2) };

	iPoint distanceMidsPositions = midPosImage - midPosLabel;

	position += distanceMidsPositions;

}

void UILabel::InitPosToWrite(UIImage* image)
{
	int midPosLabelY;
	int midPosImageY;

	midPosLabelY = position.y + (rectToDraw.h / 2);
	midPosImageY = image->GetPosition().y + (image->GetRectToDraw().h / 2);

	int distanceMidPositionY = midPosImageY - midPosLabelY;

	position.y += distanceMidPositionY;
	position.x += MARGIN;
}

//p2SString UILabel::GetText() const
//{
//	return text;
//}
//
//void UILabel::SetText(p2SString newText)
//{
//	text += newText;
//}

//SDL_Color UILabel::GetColor() const
//{
//	return color;
//}
//
//_TTF_Font* UILabel::GetFont() const
//{
//	return font;
//}

void UILabel::SetNewSizeAndTextureFont(p2SString text)
{
	//text.Cut(text.Length()-2, text.Length()-1);
	App->font->CalcSize(text.GetString(), rectToDraw.w, rectToDraw.h, font);
	textureFont = App->font->Print(text.GetString(), color, font);


	
}