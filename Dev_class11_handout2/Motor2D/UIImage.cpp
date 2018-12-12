#include "UIImage.h"

UIImage::UIImage(iPoint position, SDL_Rect rectImage, UIElement* parent, bool isEnabled) : UIElement(ImageElement, position, parent, isEnabled, rectImage)
{
}
UIImage::~UIImage()
{}

void UIImage::setRectToDraw(SDL_Rect newRectToDraw)
{
	rectToDraw = newRectToDraw;
}