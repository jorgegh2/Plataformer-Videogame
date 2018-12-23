#ifndef __j1PLAYER_H__
#define __j1PLAYER_H__

#include "j1Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "SDL/include/SDL_render.h"
#include "p2Point.h"
#include "j1Audio.h"
#include "j1Entity.h"
#include "Time.h"
#include "j1Collision.h"

struct SDL_Texture; 

enum state {

	JUMP,
	ONFLOOR, 
	ONAIR, 
	DEAD, 
	GODMODE
};

class j1Player : public Entity
{
public:
	j1Player();
	j1Player(int x, int y, SDL_Rect colliderRect);
	~j1Player();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);
	bool Start();
	bool Update(float dt);
	bool CleanUp();

	// Load / Save
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

	state SetStateFromInt(int state_as_int);
	void ResetPlayer();


	

public:
	
	state jstate;
	SDL_Texture * graphics = nullptr;
	SDL_RendererFlip flip;

	Animation* current_animation = nullptr;
	
	iPoint OriginPos;
	
	int velocityX;
	int deadcont = 0;
	int score = 0;
	int coins = 0;
	int player_lifes = 3;
	Timer timer;

	bool IsPaused = false;
	bool IsGodMode = false;
	bool IsAttacking = false;
	bool IsRunning = false;

	bool IsJumping = false;

	


	//----- Animations Awesome Game 2 ------

	Animation idle;
	Animation run;
	Animation jump;
	Animation slide1;
	Animation attack;
	Animation die;

	//---------------------

	const char*  jumping;
	const char*  dash;
	const char*  bump;
	const char*  dead;
	const char*  finishdead;
	const char*  stageclear;

	uint audio_jumping;
	uint audio_dash;
	uint audio_bump;
	uint audio_dead;
	uint audio_finishdead;
	uint audio_stageclear;
	
	Collider* offSet = nullptr;
};

#endif // __j1PLAYER_H__
