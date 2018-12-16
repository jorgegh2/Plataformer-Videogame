#include "UISlider.h"
#include "UIButton.h"

UISlider::UISlider(iPoint position, SDL_Rect barImageRect, SDL_Rect zamImageRect, bool dragable, UIElement* parent, bool isEnabled) : UIElement(SliderElement, position, parent, isEnabled, dragable, barImageRect)
{

	bar = new UIImage(position, barImageRect, false, this);
	SetParentAndChildren(bar);
	zam = new UIImage(position, zamImageRect, true, this);
	SetParentAndChildren(zam);
	horizontalSlider = true;
}

UISlider::~UISlider()
{
}

void UISlider::PreUpdate()
{
	UIElement::PreUpdate();

	previousRelativePosition = zam->GetPosition() - bar->GetPosition();

}

void UISlider::SetValueSlider(UIElement* element, int& valueToChange, int maxValue)
{
	if (minValue == -1)
	{
		minValue = valueToChange;
	}
	iPoint relativePosition = zam->GetPosition() - bar->GetPosition();
	float p = (float)(relativePosition.y) / (float)(bar->GetRectToDraw().h - zam->GetRectToDraw().h);
	float i = 27.0f / 142.0f;
	float movement = 0.0f;
	if (horizontalSlider != true) //vertical
	{
		if (int o = previousRelativePosition.y - relativePosition.y < 0) //positive increment
		{
			movement = (maxValue - minValue) * p;
			valueToChange = minValue + movement;
		}
		else if (int u = previousRelativePosition.y - relativePosition.y > 0) // negative increment
		{
			movement = (maxValue - minValue) * p;
			valueToChange = minValue + movement;
		}
	}
	/*else//horizontal
	{
	if (previousRelativePosition.y - relativePosition.y <= 0)
	{
	valueToChange += maxValue * p;
	}
	}*/

}

//void UISlider::Update(float dt)
//{
//	if (zam->GetEvent() == MouseLeftClickPressed && zam->dragable == true)
//	{
//		bool o = zam->isEnabled;
//	}
//}



