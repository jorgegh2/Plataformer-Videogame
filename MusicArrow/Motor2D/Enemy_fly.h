#ifndef __ENEMY_FLY_H__
#define __ENEMY_FLY_H__

#include "j1Entity.h"
#include "p2DynArray.h"
#include "p2Point.h"
#include "Time.h"
enum Direction;

class Enemy_Fly : public Entity
{
private:

	bool Agro = false;
	Animation fly;
	Animation attack;
	bool ShowPath = false;

public:
	iPoint originalpos;

	Enemy_Fly(int x, int y, SDL_Rect colliderRect);

	bool Awake(pugi::xml_node& config);

	bool Save(pugi::xml_node& config) const;
	bool Load(pugi::xml_node& config);

	void Move(float dt);
	void Dead();

	void DrawPath();
	bool isDead = false;  //quitar
	int i = 0;//pathcount
	bool current_in_path = false;
	p2DynArray<iPoint> enemy_path;
	int now = 0;
	Timer timer;
	bool movingLeft = false; //cambiar

	void NormalizeAnimations(float dt);

	uint flysound;
	Timer soundtimer;
};

#endif
