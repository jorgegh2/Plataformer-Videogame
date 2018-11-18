#ifndef __ENEMY_WALK_H__
#define __ENEMY_WALK_H__

#include "j1Entity.h"
#include "p2DynArray.h"
#include "p2Point.h"
#include "Time.h"
enum Direction;

class Enemy_Walk : public Entity
{
private:

	void CalculateGravity(float dt);

	//EXAMPLE
	uint zombiesound;

	Animation idle;
	Animation walk;
	Animation jump;
	

public:
	fPoint originalpos;

	Enemy_Walk(int x, int y);
	void Move(float dt);
	void Dead();
	bool isDead = false;

	int i = 0; // pathcount
	bool current_in_path = false;
	p2DynArray<iPoint> enemy_path;

	Timer timer;
	bool movingLeft = false;
	void NormalizeAnimations(float dt);
	
};

#endif

