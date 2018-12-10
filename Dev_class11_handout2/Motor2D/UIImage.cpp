#include "UIImage.h"

UIImage::UIImage(iPoint position, SDL_Rect rectImage) : UIElement(position, rectImage)
{
	type = ImageElement;

}