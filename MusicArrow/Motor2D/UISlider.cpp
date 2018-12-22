#include "UISlider.h"
#include "UIButton.h"
#include "j1Audio.h"
#include "j1App.h"

UISlider::UISlider(iPoint position, SDL_Rect barImageRect, SDL_Rect zamImageRect, bool horizontalSlider, bool dragable, UIElement* parent, bool isEnabled) : UIElement(SliderElement, position, parent, isEnabled, dragable, barImageRect)
{
	this->horizontalSlider = horizontalSlider;

	if (horizontalSlider)
	{
		bar = new UIImage(position, barImageRect, false, this);
		SetParentAndChildren(bar);
		zam = new UIImage({position.x + barImageRect.w - zamImageRect.w, position.y }, zamImageRect, true, this);
		SetParentAndChildren(zam);
	}
	else
	{
		bar = new UIImage(position, barImageRect, false, this);
		SetParentAndChildren(bar);
		zam = new UIImage(position, zamImageRect, true, this);
		SetParentAndChildren(zam);
	}
	
}

UISlider::~UISlider()
{
}

void UISlider::PreUpdate()
{
	UIElement::PreUpdate();

	previousRelativePosition = zam->GetPosition() - bar->GetPosition();

}

void UISlider::SetPositionBySlider(UIElement* element, int& valueToChange, int maxValue)
{
	if (minValue == -1)
	{
		minValue = valueToChange;
	}
	iPoint relativePosition = zam->GetPosition() - bar->GetPosition();
	float valueBetween0and1 = ValueBetween0and1();

	float movement = 0.0f;

	if (horizontalSlider != true) //vertical
	{
		if (previousRelativePosition.y - relativePosition.y < 0) //positive increment
		{
			movement = (maxValue - minValue) * valueBetween0and1;
			valueToChange = minValue + movement;
		}
		else if (previousRelativePosition.y - relativePosition.y > 0) // negative increment
		{
			movement = (maxValue - minValue) * valueBetween0and1;
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

float UISlider::ValueBetween0and1()
{
	iPoint relativePosition = zam->GetPosition() - bar->GetPosition();
	float valueBetween0and1 = 0.0f;
	if (horizontalSlider)
	{
		valueBetween0and1 = (float)(relativePosition.x) / (float)(bar->GetRectToDraw().w - zam->GetRectToDraw().w);
	}
	else
	{
		valueBetween0and1 = (float)(relativePosition.y) / (float)(bar->GetRectToDraw().h - zam->GetRectToDraw().h);
	}


	return valueBetween0and1;
}

//void UISlider::Update(float dt)
//{
//	if (zam->GetEvent() == MouseLeftClickPressed && zam->dragable == true)
//	{
//		bool o = zam->isEnabled;
//	}
//}



