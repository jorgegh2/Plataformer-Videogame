#ifndef _UISLIDER_
#define _UISLIDER_

#include "UIElement.h"
#include "UIImage.h"
//#include "p2SString.h"

class UISlider : public UIElement
{
public:
	UISlider(iPoint position, SDL_Rect barImage, SDL_Rect zamImage);
	virtual ~UISlider();

	void PreUpdate();
	void Update(float dt);

private:
	UIImage* bar;
	UIImage* zam;
};
#endif