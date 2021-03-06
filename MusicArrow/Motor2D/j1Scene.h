#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"

#include "j1Fonts.h"




struct SDL_Texture;
class UIImage;
class UIButton;
class UILabel;
class UISlider;


class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake(pugi::xml_node& node);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Load / Save
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;
	void BackMainMenu() const;

	void PauseOrResume() const;

	p2SString current_scene;

	uint audio_rollover;
	uint audio_click;

	

private:

	UIImage* panelInGame = nullptr;


	UIButton* resumeButton = nullptr;
	UIButton* saveButton = nullptr;
	UIButton* loadButton = nullptr;
	UIButton* mainMenu = nullptr;

	UILabel* music = nullptr;
	UILabel* fx = nullptr;
	UISlider* musicSlider = nullptr;
	UISlider* fxSlider = nullptr;

};

#endif // __j1SCENE_H__