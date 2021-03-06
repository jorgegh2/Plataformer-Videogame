#ifndef __OBJECT_COIN_H__
#define __OBJECT_COIN_H__

#include "j1Entity.h"
#include "p2DynArray.h"
#include "p2Point.h"
#include "Time.h"

class Object_Coin : public Entity
{
private:

	uint coin_sound;
	Animation idle;

public:

	iPoint originalpos;

	Object_Coin(int x, int y, SDL_Rect colliderRect);

	bool Save(pugi::xml_node& config) const;
	bool Load(pugi::xml_node& config);
	void Move(float dt);
	bool isPlayer = false;

	Timer timer;

	void NormalizeAnimations(float dt);

};

#endif
