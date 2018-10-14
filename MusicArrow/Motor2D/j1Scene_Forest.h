#ifndef __j1SCENE_FOREST_H__
#define __j1SCENE_FOREST_H__

#include "j1Module.h"



class j1Scene_Forest : public j1Module
{
public:

	j1Scene_Forest();
	
	// Destructor
	~j1Scene_Forest();

	// Called before render
	bool j1Scene_Forest::Awake(pugi::xml_node& config);
	
	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update(float dt);

	// Called before quitting
	bool CleanUp();

private:
};

#endif // __j1SCENE_FOREST_H__
