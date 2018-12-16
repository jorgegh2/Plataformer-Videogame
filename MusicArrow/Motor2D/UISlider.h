#ifndef _UISLIDER_
#define _UISLIDER_

#include "UIElement.h"
#include "UIImage.h"
//#include "p2SString.h"

class UISlider : public UIElement
{
public:
	UISlider(iPoint position, SDL_Rect barImage, SDL_Rect zamImage, bool dragable, UIElement* parent = nullptr, bool isEnabled = true);
	virtual ~UISlider();

	void PreUpdate();
	//void Update(float dt);
	void SetValueSlider(UIElement* element, int& valueToChange, int maxValue);

private:
	UIImage * bar = nullptr;
	UIImage* zam = nullptr;
	iPoint previousRelativePosition;
	int minValue = -1;
};
#endif