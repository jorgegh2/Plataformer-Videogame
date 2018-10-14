#ifndef __j1SCENE_WINTER_H__
#define __j1SCENE_WINTER_H__

#include "j1Module.h"



class j1Scene_Winter : public j1Module
{
public:

	j1Scene_Winter();

	// Destructor
	virtual ~j1Scene_Winter();

	// Called before render is available

	bool Awake(pugi::xml_node& node);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update(float dt);

	// Called before quitting
	bool CleanUp();




private:
};

#endif // __j1SCENE_WINTER_H__

