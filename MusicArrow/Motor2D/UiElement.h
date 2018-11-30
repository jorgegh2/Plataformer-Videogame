#ifndef _UIELEMENT_
#define _UIELEMENT_

#include "SDL/include/SDL.h"
#include "p2Defs.h"
#include "p2Point.h"
#include "j1Textures.h"

class j1Module;

enum ElementType
{
	NoTypeElement,
	ButtonElement,
	LabelElement,
	ImageElement,
	SliderElement
};

enum EventElement
{
	NoEventElement,
	MouseEnterEvent,
	MouseLeaveEvent,
	MouseRightClickEvent,
	MouseLeftClickEvent,
	FocusEventElement
};

class UIElement
{
public:
	UIElement(iPoint, j1Module*, bool);

	virtual void Update(float);
	virtual void Draw();
	virtual void DebugDraw() const;
	virtual void SetSliderButtonPos(int);
	void SetParent(UIElement*);
	void SetLocalPosition(iPoint);
	void ChangeTexture(SDL_Texture*);
	void ChangeTextureRect(SDL_Rect);
	virtual ~UIElement();

	ElementType type = ElementType::NoTypeElement;
	EventElement eventElement = EventElement::NoEventElement;
	SDL_Rect rectUi = { 0,0,0,0 };
	uint positionToDraw = 0;
	iPoint positionUi = { 0,0 };
	bool dragable = false;
	bool toDelete = false;
	iPoint localPosition = { 0,0 };
	
protected:
	UIElement* parent = nullptr;
	SDL_Texture *texture = nullptr;
	j1Module* listener = nullptr;
	iPoint mouse = { 0,0 };
	int mousePositionDragX = 0, mousePositionDragY = 0;
	

};

#endif

