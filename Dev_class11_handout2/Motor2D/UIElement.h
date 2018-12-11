#ifndef __UIELEMENT_H__
#define __UIELEMENT_H__

#include "SDL/include/SDL_rect.h"
#include "p2Point.h"
#include "p2List.h"

struct SDL_Texture;

enum ElementType { NoTypeElement, ButtonElement, LabelElement, ImageElement, SliderElement };

enum EventElement {
	NoEventElement, MouseEnterEvent, MouseLeaveEvent, MouseRightClickEvent, MouseLeftClickEvent,
	FocusEventElement
};

class UIElement
{
public: 
	UIElement(ElementType type, iPoint position, UIElement* parent, SDL_Rect rectToDraw = { 0,0,0,0 } );
		///Second constructor if there are a rect but no parent is necessary.
		///UIElement(ElementType type, iPoint position, SDL_Rect rectToDraw = { 0,0,0,0 });
	void Update(float dt);
	void Draw(SDL_Texture* atlas);
	//virtual void DebugDraw() const;
	//virtual void SetSliderButtonPos(int);
	//void SetParent(UIElement*);
	//void SetLocalPosition(iPoint);
	virtual ~UIElement();
	virtual SDL_Texture* GetUITexture();
	UIElement* GetParent() const;
	
protected:
	ElementType type;
	//EventElement eventElement;
	//uint positionToDraw;
	//bool toDelete;

	iPoint position;
	SDL_Rect rectToDraw;
	UIElement* parent;
	UIElement* children;
	p2List<UIElement*> listChildren;
	
	

};

#endif
