#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "UIElement.h"
#include "UIButton.h"
#include "UIImage.h"
#include "UILabel.h"
#include "UIBoxText.h"
#include "UISlider.h"


#define CURSOR_WIDTH 2
#define MAX_GUI_ENTITIES 50

class UIImage;
class UILabel;
struct _TTF_Font;
class p2SString;
struct SDL_Texture;
// ---------------------------------------------------
class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	//// Called after all Updates
	//bool PostUpdate();

	// Call all updates
	bool Update(float dt);

	// Called before quitting
	bool CleanUp();

	//Draw all Gui's entities
	void DrawAll();

	// Gui creation functions
	UIImage* CreateImage(iPoint position, SDL_Rect rectImage, bool dragable = false);
	UILabel* CreateLabel(iPoint position, p2SString text, SDL_Color color = { 255, 255, 255, 255 }, _TTF_Font* font = NULL, bool dragable = false);
	UIButton* CreateButton(iPoint position, SDL_Rect[], p2SString text = nullptr, SDL_Color color = { 255, 255, 255, 255 }, _TTF_Font* font = NULL, bool dragable = false);
	UIBoxText* CreateBoxText(iPoint position, SDL_Rect rectImage, p2SString text = nullptr, SDL_Color color = { 255, 255, 255, 255 }, _TTF_Font* font = NULL, bool dragable = false);
	UISlider* CreateSlider(iPoint position, SDL_Rect barImageRect, SDL_Rect zamImageRect, bool dragable = false);

	SDL_Texture* GetAtlas() const;



private:

	SDL_Texture* atlas = nullptr;
	p2SString atlas_file_name;
	p2List<UIElement*> GuiEntities;
	p2List_item<UIElement*>* item;
	//bool drawDebug;

};

#endif // __j1GUI_H__