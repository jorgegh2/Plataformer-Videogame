#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "UIElement.h"
#include "p2DynArray.h"
#include "UIButton.h"
#include "UIImage.h"
#include "UILabel.h"


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
	bool Update(float dt);

	// Called before quitting
	bool CleanUp();

	//Draw all Gui's entities
	void Draw() const;

	// TODO 2: Create the factory methods
	// Gui creation functions
	
	void CreateImage(iPoint position, SDL_Rect rectImage);
	void CreateLabel(iPoint position, p2SString text, SDL_Color color,  _TTF_Font* font);
	//UIButton* CreateButton(iPoint, SDL_Rect, SDL_Rect, SDL_Rect, bool dragable = false);
	//UISlider* CreateSlider(iPoint, SDL_Rect, SDL_Rect, float);
	//void SortByDrawOrder();
	const SDL_Texture* GetAtlas() const;
	//bool DeleteUIElements();
	//bool needOrderList;


private:

	SDL_Texture* atlas;
	p2SString atlas_file_name;
	UIElement* GuiEntities[MAX_GUI_ENTITIES];
	//bool drawDebug;

};

#endif // __j1GUI_H__