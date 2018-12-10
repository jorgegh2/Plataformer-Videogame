#ifndef __UIELEMENT_H__
#define __UIELEMENT_H__

#include "SDL/include/SDL_rect.h"
#include "p2Point.h"

struct SDL_Texture;

enum ElementType { NoTypeElement, ButtonElement, LabelElement, ImageElement, SliderElement };

enum EventElement {
	NoEventElement, MouseEnterEvent, MouseLeaveEvent, MouseRightClickEvent, MouseLeftClickEvent,
	FocusEventElement
};

class UIElement
{
public: 
	UIElement(iPoint position, SDL_Rect rectToDraw = {0,0,0,0});
	void Update(float dt);
	void Draw(SDL_Texture* atlas);
	//virtual void DebugDraw() const;
	//virtual void SetSliderButtonPos(int);
	//void SetParent(UIElement*);
	//void SetLocalPosition(iPoint);
	virtual ~UIElement();
	
protected:
	ElementType type;
	EventElement eventElement;
	uint positionToDraw;
	bool toDelete;
	iPoint position;
	SDL_Rect rectToDraw;
	SDL_Texture* textureFont; //
	

};

#endif
