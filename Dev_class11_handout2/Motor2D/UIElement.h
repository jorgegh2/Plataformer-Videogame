#ifndef __UIELEMENT_H__
#define __UIELEMENT_H__

#include "SDL/include/SDL_rect.h"
#include "p2Point.h"
#include "p2List.h"

struct SDL_Texture;

enum ElementType { NoTypeElement, ButtonElement, LabelElement, ImageElement, SliderElement };

enum EventElement {
	NoEventElement, MouseEnterEvent, MouseInside, MouseLeaveEvent, MouseLeftClickEvent, MouseLeftClickPressed //FocusEventElement
};

class UIElement
{
public: 
	UIElement(ElementType type, iPoint position, UIElement* parent, SDL_Rect rectToDraw = { 0,0,0,0 } );
		///Second constructor if there are a rect but no parent is necessary.
		///UIElement(ElementType type, iPoint position, SDL_Rect rectToDraw = { 0,0,0,0 });
	virtual void Update(float dt);
	virtual void PreUpdate();
	void Draw(SDL_Texture* atlas);
	SDL_Rect GetRectToDraw();

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
