#ifndef __ENEMY_BALL_H__
#define __ENEMY_BALL_H__

#include "j1Entity.h"
#include "p2DynArray.h"
#include "p2Point.h"
#include "Time.h"

class Enemy_Ball : public Entity
{
private:

	uint ball_sound;
	Animation idle;

public:

	iPoint originalpos;

	Enemy_Ball(int x, int y, SDL_Rect colliderRect);

	bool Save(pugi::xml_node& config) const;
	bool Load(pugi::xml_node& config);
	void Move(float dt);
	bool isDead = false;

	Timer timer;

	void NormalizeAnimations(float dt);

};

#endif

