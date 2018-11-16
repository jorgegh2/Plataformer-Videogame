#ifndef __j1PLAYER_H__
#define __j1PLAYER_H__

#include "j1Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "SDL/include/SDL_render.h"
#include "p2Point.h"
#include "j1Audio.h"
#include "j1Entity.h"

struct SDL_Texture;
struct SDL_Rect;
struct Mix_Chunk;
struct Mix_Music;
struct Collider;


enum state {JUMP, ONFLOOR, ONAIR, LANDING, DEAD, GODMODE};

class j1Player : public Entity
{
public:
	j1Player();
	j1Player(int x, int y);
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
	
	iPoint StartPoint;
	
	float velocityX;
	
	int jumpCount;
	int dashCount;
	int godmodeCount;
	


	//----- Animations Awesome Game 2 ------

	Animation idle;
	Animation alert;
	Animation walk;
	Animation run;
	Animation jump;
	Animation fall;
	Animation shot;
	Animation hit;
	Animation die;

	//---------------------

	/*Mix_Chunk* helix_sound = nullptr;
	Mix_Chunk* laser_sound = nullptr;
	Mix_Chunk* basic_attack_sound = nullptr;
	Mix_Chunk* player_death = nullptr;
	Mix_Chunk* change_weapon_sound = nullptr;*/

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
	
	bool destroyed = true;
	

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
