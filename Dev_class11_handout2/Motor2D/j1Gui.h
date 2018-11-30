#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "GuiEntity.h"
#include "p2DynArray.h"

#define CURSOR_WIDTH 2
#define MAX_GUI_ENTITIES 50

// TODO 1: Create your structure of classes

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
	//bool PreUpdate();

	//// Called after all Updates
	//bool PostUpdate();

	// Call all updates
	void Update();

	// Called before quitting
	bool CleanUp();

	//Draw all Gui's entities
	void Draw() const;

	// TODO 2: Create the factory methods
	// Gui creation functions
	
	UIImage* CreateImage(iPoint, SDL_Rect);
	UILabel* CreateLabel(iPoint, char*, SDL_Color, _TTF_Font*);
	UIButton* CreateButton(iPoint, SDL_Rect, SDL_Rect, SDL_Rect, bool dragable = false);
	//UISlider* CreateSlider(iPoint, SDL_Rect, SDL_Rect, float);
	void SortByDrawOrder();
	const SDL_Texture* GetAtlas() const;
	bool DeleteUIElements();
	bool needOrderList;

	const SDL_Texture* GetAtlas() const;

	

private:

	SDL_Texture* atlas;
	p2SString atlas_file_name;
	p2List<UIElement*> UiElement; // cambiar a array
	bool drawDebug;

};

#endif // __j1GUI_H__