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
	UIElement(ElementType type, iPoint position, UIElement* parent, bool isEnabled, bool Dragable, SDL_Rect rectToDraw = { 0,0,0,0 });
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
	SDL_Rect GetRectToDraw();
	iPoint GetPosition() const;
	bool IsMouseInsideElement(int MarginX = 0, int marginY = 0);
	EventElement GetEvent() const;
	void SetParentAndChildren(UIElement* children);
	void DragUIElement();
	void MoveInParentLimits(int movementX, int);

protected:
	ElementType type;
	EventElement Event = NoEventElement;
	//uint positionToDraw;
	//bool toDelete;
	int posX = -1;
	int posY = -1;
	bool horizontalSlider = false;

	SDL_Rect rectToDraw;
	UIElement* parent = nullptr;

	bool dragable;
	iPoint mousePositionFirst;
	iPoint mousePositionFinal;


public:
	bool isEnabled = true;
	p2List<UIElement*> listChildren;
	iPoint position;
};

#endif

