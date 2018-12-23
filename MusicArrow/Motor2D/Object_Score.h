#ifndef __OBJECT_SCORE_H__
#define __OBJECT_SCORE_H__

#include "j1Entity.h"
#include "p2DynArray.h"
#include "p2Point.h"
#include "Time.h"

class Object_Score : public Entity
{
private:

	uint coin_sound;
	
public:

	iPoint originalpos;

	Object_Score(int x, int y, SDL_Rect colliderRect);

	bool Save(pugi::xml_node& config) const;
	bool Load(pugi::xml_node& config);
	void Move(float dt);
	bool isDead = false;
	bool isPlayer = false;

	

};

#endif

