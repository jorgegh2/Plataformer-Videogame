#ifndef _COIN_
#define _COIN_


#include "j1Entity.h"
#include "Animation.h"




class Coin : public Entity
{
public:
	Coin(int, int);

	void Move(float);
	void NormalizeAnimations(float);
	void Dead(float dt);

private:
	Animation rotateAnimation;
	bool isDead = false;
	uint sound;
};


#endif
