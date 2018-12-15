#ifndef _UILABEL_H_
#define _UILABEL_H_

#include "UIElement.h"
#include "p2SString.h"
#include "p2Point.h"



struct _TTF_Font;
struct SDL_Texture;
class UIImage;

class UILabel : public UIElement
{
public:
	UILabel(iPoint position, p2SString text, SDL_Color color, _TTF_Font* font, bool dragable, UIElement* parent = nullptr, bool isEnabled = true);
	virtual ~UILabel();
	void CentralizeLabel(UIImage* image);
	void InitPosToWrite(UIImage* image);

	SDL_Texture* GetUITexture();
	SDL_Texture* textureFont; //
	/*p2SString GetText() const;*/
	//SDL_Color GetColor() const;
	////_TTF_Font* GetFont() const;
	//void SetText(p2SString newText);
	void SetNewSizeAndTextureFont(p2SString text);

private:
	SDL_Color color;
	_TTF_Font* font;

public:
	p2SString text;
};

#endif

