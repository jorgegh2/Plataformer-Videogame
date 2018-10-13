#ifndef __j1PLAYER_H__
#define __j1PLAYER_H__

#include "j1Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "SDL/include/SDL_render.h"

struct SDL_Texture;
struct SDL_Rect;
struct Mix_Chunk;
struct Collider;


enum state {NONE, JUMP, ONFLOOR, ONAIR, WALK};

class j1Player : public j1Module
{
public:
	j1Player();
	~j1Player();

	bool Start();
	bool Update(float dt);
	bool CleanUp();

	void OnCollision(Collider*, Collider*);

public:
	
	state jstate;
	SDL_Texture * graphics = nullptr;
	SDL_RendererFlip flip;
	

	bool locked_to_right = false;
	bool locked_to_left = false;
	uint margen = 3;

	Animation* current_animation = nullptr;
	Animation* anim_turbo = nullptr;
	
	fPoint position;
	fPoint location;
	fPoint speed;
	float velocityX;
	float myGravity;
	/*float maxFallSpeed;
	float jumpForce;
	float currentJumpForce;*/
	float deltaTime;

	Animation up;
	Animation down;
	Animation upback;
	Animation downback;

	Animation turbo_idle;
	Animation turbo_up;
	Animation turbo_down;

	//----- Animations Awesome Game 2 ------

	Animation idle;
	Animation alert;
	Animation walk;
	Animation run;
	Animation jump;
	Animation shot;
	Animation hit;
	Animation die;

	//---------------------

	Mix_Chunk* helix_sound = nullptr;
	Mix_Chunk* laser_sound = nullptr;
	Mix_Chunk* basic_attack_sound = nullptr;
	Mix_Chunk* player_death = nullptr;
	Mix_Chunk* change_weapon_sound = nullptr;

	
	bool destroyed = true;
	bool god_mode = false;

	uint life = 1;
	uint time_final = 0;
	uint time_init = 0;
	bool time_finished = true;
	uint Bullet_time_init = 0;
	uint Bullet_delay;
	bool Reset_time_bullets = true;

	bool reverse = false;


	Collider* c_player = nullptr;
	Collider* offSet = nullptr;

	// Vars to check if the buttons are still pressed
	bool a_pressed = false;
	bool x_pressed = false;
	bool b_pressed = false;

	bool shoot = false; // so that the player does not shot forever
	bool change = false; // so that the player does not change weapons forever
	bool powerup = false;
	bool powerup_desincrement = false;

	bool player_up = false;
	bool player_down = false;
	bool player_idle = false;

public: // so we can access from UI module and blit the HUD textures or images
	/*enum CHANGE_WEAPON
	{
		BASIC_ATTACK = 0,
		LASER,
		BACK_SHOOT,
		HELIX
	} change_weapon = CHANGE_WEAPON::BASIC_ATTACK;


	enum POWER_UPS
	{
		POWER_UP_BASIC = 0,
		POWER_UP_1,
		POWER_UP_2,
		POWER_UP_3,
		POWER_UP_4,
		POWER_UP_5,
		POWER_UP_6

	} power_up = POWER_UPS::POWER_UP_BASIC;*/
};

#endif // __j1PLAYER_H__
