#ifndef _UISLIDER_
#define _UISLIDER_

#include "UIElement.h"
#include "UIImage.h"

class UISlider : public UIElement
{
public:
	UISlider(iPoint position, SDL_Rect barImage, SDL_Rect zamImage, bool horizontalSlider, bool dragable, UIElement* parent = nullptr, bool isEnabled = true);
	virtual ~UISlider();

	void PreUpdate();
	void SetPositionBySlider(UIElement* element, int& valueToChange, int maxValue);
	void SetValueBySlider(int maxValue);
	float ValueBetween0and1();

private:
	UIImage * bar = nullptr;
	UIImage* zam = nullptr;
	iPoint previousRelativePosition;
	int minValue = -1;
};
#endif