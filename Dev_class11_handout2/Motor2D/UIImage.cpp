#include "UIImage.h"

UIImage::UIImage(iPoint position, SDL_Rect rectImage, UIElement* parent) : UIElement(ImageElement, position, parent, rectImage)
{
}
UIImage::~UIImage()
{}

void UIImage::setRectToDraw(SDL_Rect newRectToDraw)
{
	rectToDraw = newRectToDraw;
}