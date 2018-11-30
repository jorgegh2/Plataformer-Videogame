#ifndef __GUIENTITY_H__
#define __GUIENTITY_H__

#include "SDL/include/SDL_rect.h"
#include "p2Point.h"
class SDL_Texture;

enum ElementType { NoTypeElement, ButtonElement, LabelElement, ImageElement, SliderElement };

enum EventElement {
	NoEventElement, MouseEnterEvent, MouseLeaveEvent, MouseRightClickEvent, MouseLeftClickEvent,
	FocusEventElement
};

class UIElement
{
public: 
	UIElement(iPoint);
	virtual void Update(float);
	virtual void Draw();
	virtual void DebugDraw() const;
	virtual void SetSliderButtonPos(int);
	void SetParent(UIElement*);
	void SetLocalPosition(iPoint);
	virtual ~UIElement();
	
protected:
	ElementType type;
	EventElement eventElement;
	uint positionToDraw;
	bool toDelete;
	iPoint localPosition;
	

};

#endif
