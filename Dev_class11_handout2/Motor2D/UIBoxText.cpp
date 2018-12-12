#include "UIBoxText.h"
#include "UIElement.h"
#include "j1Render.h"
#include "j1App.h"

UIBoxText::UIBoxText(iPoint position, SDL_Rect rectImage, p2SString text, SDL_Color color, _TTF_Font* font, UIElement* parent) : UIElement(BoxTextElement, position, parent)
{
	BoxTextImage = new UIImage(position, rectImage, this);
	listChildren.add(BoxTextImage);

	//funcion para centrar el texto y sacar su posicion relativa.
	BoxTextLabelInitial = new UILabel(position, text, color, font, this);
	listChildren.add(BoxTextLabelInitial);

	finalRect.x = position.x + 20;
	finalRect.y = position.y + 100;
	finalRect.w = 5;
	finalRect.h = 20;

	BoxTextLabel = new UILabel(position, text, color, font, this);
	listChildren.add(BoxTextLabelInitial);

}

UIBoxText::~UIBoxText()
{

}

void UIBoxText::printFinalQuad(SDL_Rect finalRect)
{
	App->render->DrawQuad(finalRect, 255, 255, 255, 255);
}

void UIBoxText::Update(float dt)
{
	printFinalQuad(finalRect);
}
