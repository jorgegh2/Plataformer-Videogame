#ifndef __UIELEMENT_H__
#define __UIELEMENT_H__

#include "SDL/include/SDL_rect.h"
#include "p2Point.h"
#include "p2List.h"

#define MARGIN 20;

struct SDL_Texture;

enum ElementType { NoTypeElement, ButtonElement, LabelElement, ImageElement, SliderElement, BoxTextElement };

enum EventElement {
	NoEventElement, MouseEnterEvent, MouseInside, MouseLeaveEvent, MouseLeftClickEvent, MouseLeftClickPressed, MouseLeftClickLeave //FocusEventElement
};

class UIElement
{
public: 
	UIElement(ElementType type, iPoint position, UIElement* parent, bool isEnabled, SDL_Rect rectToDraw = { 0,0,0,0 }, bool Dragable = false );
		///Second constructor if there are a rect but no parent is necessary.
		///UIElement(ElementType type, iPoint position, SDL_Rect rectToDraw = { 0,0,0,0 });
	virtual ~UIElement();

	virtual void PreUpdate();
	virtual void Update(float dt);

	void Draw(SDL_Texture* atlas);

	//virtual void DebugDraw() const;
	//virtual void SetSliderButtonPos(int);
	//void SetParent(UIElement*);
	//void SetLocalPosition(iPoint);

	virtual SDL_Texture* GetUITexture();
	UIElement* GetParent() const;
	SDL_Rect GetRectToDraw() const;
	iPoint GetPosition() const;
	bool IsMouseInsideElement();
	EventElement GetEvent() const;

	void DragUIElement();
	
protected:
	ElementType type;
	EventElement Event = NoEventElement;
	//uint positionToDraw;
	//bool toDelete;

	iPoint position;
	SDL_Rect rectToDraw;
	UIElement* parent;
	UIElement* children;
	p2List<UIElement*> listChildren;

	bool dragable;
	
	
public:
	bool isEnabled = true;
};

#endif
