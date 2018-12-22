#ifndef __j1SCENEMENU_H__
#define __j1SCENEMENU_H__

#include "j1Module.h"

#define MIX_MAX_VOLUME 128

class UIButton;
class UIImage;
class UILabel;
class UISlider;

class j1SceneMenu : public j1Module
{
public:

	j1SceneMenu();

	// Destructor
	virtual ~j1SceneMenu();

	// Called before render is available

	bool Awake(pugi::xml_node& node);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update(float dt);

	// Called before quitting
	bool CleanUp();

private:

	UIButton* playButton = nullptr;
	UIButton* continueButton = nullptr;
	UIButton* settingsButton = nullptr;
	UIButton* creditsButton = nullptr;
	UIButton* exitButton = nullptr;

	UIImage* panel = nullptr;
	UILabel* music = nullptr;
	UILabel* fx = nullptr;
	UISlider* musicSlider = nullptr;
	UISlider* fxSlider = nullptr;

	UIImage* panelCredits = nullptr;
	UILabel* Author1 = nullptr;
	UILabel* Author2 = nullptr;

	SDL_Texture* bg = nullptr;
	SDL_Rect bgRect;

public: 
	bool isLoad = false;

};

#endif // __j1SCENE_WINTER_H__

