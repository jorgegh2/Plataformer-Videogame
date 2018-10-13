#ifndef __j1SCENE_WINTER_H__
#define __j1SCENE_WINTER_H__

#include "j1Scene.h"



class j1Scene_Winter : public j1Scene
{
public:

	j1Scene_Winter();

	// Destructor
	virtual ~j1Scene_Winter();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();




private:
};

#endif // __j1SCENE_WINTER_H__
