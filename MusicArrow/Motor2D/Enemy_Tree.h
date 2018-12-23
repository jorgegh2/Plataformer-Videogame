#ifndef __ENEMY_TREE_H__
#define __ENEMY_TREE_H__

#include "j1Entity.h"
#include "p2DynArray.h"
#include "p2Point.h"
#include "Time.h"

class Enemy_Tree : public Entity
{
private:

	void CalculateGravity(float dt);

	uint tree_sound;
	Animation walk;

public:

	iPoint originalpos;

	Enemy_Tree(int x, int y, SDL_Rect colliderRect);

	bool Save(pugi::xml_node& config) const;
	bool Load(pugi::xml_node& config);

	void Move(float dt);
	bool isDead = false;

	Timer timer;
	void NormalizeAnimations(float dt);

};

#endif
