#include "UIImage.h"

UIImage::UIImage(iPoint position, SDL_Rect rectImage, UIElement* parent) : UIElement(ImageElement, position, parent, rectImage)
{
}