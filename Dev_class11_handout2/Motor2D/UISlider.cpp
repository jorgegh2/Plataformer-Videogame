#include "UISlider.h"
#include "UIButton.h"

UISlider::UISlider(iPoint position, SDL_Rect barImageRect, SDL_Rect zamImageRect, bool dragable, UIElement* parent, bool isEnabled) : UIElement(SliderElement, position, parent, isEnabled, dragable, barImageRect)
{
	
	bar = new UIImage(position, barImageRect, false, this);
	SetParentAndChildren(bar);
	position.x -= 5;//puntual
	zam = new UIImage(position, zamImageRect, true, this);
	SetParentAndChildren(zam);
}

UISlider::~UISlider()
{
}

//void UISlider::Update(float dt)
//{
//	if (zam->GetEvent() == MouseLeftClickPressed && zam->dragable == true)
//	{
//		bool o = zam->isEnabled;
//	}
//}

