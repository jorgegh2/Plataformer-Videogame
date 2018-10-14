#ifndef _j1PARTICLES_H__
#define __j1PARTICLES_H__

#include "j1Module.h"
#include "Animation.h"
//#include "Globals.h"
#include "p2Point.h"
#include "j1Collision.h"

#define MAX_ACTIVE_PARTICLES 300 

struct SDL_Texture;

enum COLLIDER_TYPE;

struct Particle
{
	int type_particle;
	Collider* collider = nullptr;
	Animation anim;
	uint fx = 0;
	iPoint position;
	iPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;

	int tipe;

	Particle();
	Particle(const Particle& p);
	virtual ~Particle();
	bool Update();
	enum TYPE_PARTICLE {
		SHOOT = 0,
		EXPLOSION,
		EXPLOSION_ENEMY,
		SHOOT_ENEMY
	} Type = TYPE_PARTICLE::SHOOT;
};

class j1Particles : public j1Module
{
public:
	j1Particles();
	~j1Particles();

	bool Start();
	bool Update(float dt);
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	void AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type = COLLIDER_NONE, Uint32 delay = 0);

private:

	/*SDL_Texture * graphics = nullptr;
	SDL_Texture* graphics2 = nullptr;
	SDL_Texture* graphics3 = nullptr;
	SDL_Texture* enemy15shotgraphics = nullptr;*/
	Particle* active[MAX_ACTIVE_PARTICLES];

public:


	/*Particle explosion;
	Particle explosion2;
	Particle enemy_explosion1;
	Particle enemy_explosion2;
	Particle enemy_explosion3;

	Particle basic_shoot_0_up;
	Particle basic_shoot_0_down;

	Particle basic_shoot_1;
	Particle basic_shoot_1_up;
	Particle basic_shoot_1_down;

	Particle basic_shoot_2;
	Particle basic_shoot_2_up;
	Particle basic_shoot_2_down;

	Particle basic_shoot_3_up;
	Particle basic_shoot_3_down;

	Particle basic_shoot_4_up;
	Particle basic_shoot_4_down;

	Particle basic_shoot_5_up;
	Particle basic_shoot_5_down;

	Particle basic_shoot_6_up;
	Particle basic_shoot_6_down;

	Particle laser_0;

	Particle laser_1;
	Particle laser_1_5;

	Particle laser_2;
	Particle laser_2_5;

	Particle laser_3_up;
	Particle laser_3_down;
	Particle laser_3_up_back;
	Particle laser_3_down_back;

	Particle laser_4_up;
	Particle laser_4_down;
	Particle laser_4_up_back;
	Particle laser_4_down_back;

	Particle laser_5_up;
	Particle laser_5_down;
	Particle laser_5_up_back;
	Particle laser_5_down_back;

	Particle laser_6_up;
	Particle laser_6_down;
	Particle laser_6_up_back;
	Particle laser_6_down_back;



	Particle back_shoot_0;
	Particle back_shoot_0_up;
	Particle back_shoot_0_down;
	Particle back_shoot_0_back;
	Particle back_shoot_0_5;

	Particle back_shoot_1_5;

	Particle back_shoot_2_diagonal_up;
	Particle back_shoot_2_diagonal_down;

	Particle back_shoot_3_back;
	Particle back_shoot_3_diagonal_up;
	Particle back_shoot_3_diagonal_down;


	// For normal and power up 1
	Particle helix_01_1;  // Particle that goes downwards
	Particle helix_01_2;  // Particle that goes upwards
						  // For power up 1
	Particle helix_01_3;  // Particle at the middle
						  // For power up 2 and 3
	Particle helix_02_1;  // Particle that goes downwards
	Particle helix_02_2;  // Particle that goes upwards
	Particle helix_02_3;  // Particle at the middle
						  // For power up 3 (more horizontal speed)
	Particle helix_03_1;  // downwards
	Particle helix_03_2;  // upwards
						  // PU 4 Same as 03_1 but with bigger bullete (last animation frame)
	Particle helix_04_1;
	Particle helix_04_2;
	// PU 5
	Particle helix_05_1;  // downwards
	Particle helix_05_2;  // upwards
	Particle helix_05_3;  // middle
						  // PU 6
	Particle helix_06_1;  // downwards
	Particle helix_06_2;  // upwards


	Particle enemy15shot;*/

};

#endif // __j1PARTICLES_H__