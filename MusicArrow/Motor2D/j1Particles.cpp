#include <math.h>
//#include "Globals.h"
#include "j1App.h"
//#include "ModuleTextures.h"
//#include "ModuleRender.h"
#include "j1Particles.h"
#include "j1Collision.h"
//#include <iostream>
#include "SDL/include/SDL_timer.h"

j1Particles::j1Particles() : j1Module()
{

	name.create("particles");

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;

	/*// Basic_shoot 0_up
	basic_shoot_0_up.anim.PushBack({ 58, 91, 11, 4 });
	basic_shoot_0_up.anim.PushBack({ 24, 37, 11, 6 });
	basic_shoot_0_up.anim.PushBack({ 24, 39, 11, 4 });
	basic_shoot_0_up.anim.loop = false;
	basic_shoot_0_up.anim.speed = 0.3f;
	basic_shoot_0_up.speed.x = 8;
	basic_shoot_0_up.life = 1200;


	// Basic_shoot 0_down
	basic_shoot_0_down.anim.PushBack({ 58, 91, 11, 4 });
	basic_shoot_0_down.anim.PushBack({ 24, 39, 11, 4 });
	basic_shoot_0_down.anim.PushBack({ 24, 37, 11, 6 });
	basic_shoot_0_down.anim.loop = false;
	basic_shoot_0_down.anim.speed = 0.3f;
	basic_shoot_0_down.speed.x = 8;
	basic_shoot_0_down.life = 1200;
	basic_shoot_0_down.type_particle = 1;


	// Basic_shoot 1
	basic_shoot_1.anim.PushBack({ 58, 91, 11, 4 });
	basic_shoot_1.anim.PushBack({ 28, 39, 15, 4 });
	basic_shoot_1.anim.PushBack({ 26, 39, 13, 4 });
	basic_shoot_1.anim.PushBack({ 24, 39, 11, 4 });
	basic_shoot_1.anim.loop = false;
	basic_shoot_1.anim.speed = 0.3f;
	basic_shoot_1.speed.x = 8;
	basic_shoot_1.life = 1200;


	// Basic_shoot 1_up
	basic_shoot_1_up.anim.PushBack({ 58, 91, 11, 4 });
	basic_shoot_1_up.anim.PushBack({ 24, 35, 11, 8 });
	basic_shoot_1_up.anim.PushBack({ 24, 37, 11, 6 });
	basic_shoot_1_up.anim.PushBack({ 24, 39, 11, 4 });
	basic_shoot_1_up.anim.loop = false;
	basic_shoot_1_up.anim.speed = 0.3f;
	basic_shoot_1_up.speed.x = 8;
	basic_shoot_1_up.life = 1200;


	// Basic_shoot 1_down
	basic_shoot_1_down.anim.PushBack({ 58, 91, 11, 4 });
	basic_shoot_1_down.anim.PushBack({ 24, 39, 11, 4 });
	basic_shoot_1_down.anim.PushBack({ 24, 37, 11, 6 });
	basic_shoot_1_down.anim.PushBack({ 24, 35, 11, 8 });
	basic_shoot_1_down.anim.loop = false;
	basic_shoot_1_down.anim.speed = 0.3f;
	basic_shoot_1_down.speed.x = 8;
	basic_shoot_1_down.life = 1200;
	basic_shoot_1_down.type_particle = 2;

	// Basic_shoot 2
	basic_shoot_2.anim.PushBack({ 26, 63, 15, 6 });
	basic_shoot_2.anim.PushBack({ 24, 63, 13, 6 });
	basic_shoot_2.anim.PushBack({ 22, 63, 15, 6 }); //
	basic_shoot_2.anim.PushBack({ 20, 63, 17, 6 });
	basic_shoot_2.anim.PushBack({ 18, 63, 19, 6 });
	basic_shoot_2.anim.PushBack({ 16, 63, 21, 6 });
	basic_shoot_2.anim.loop = false;
	basic_shoot_2.anim.speed = 0.3f;
	basic_shoot_2.speed.x = 8;
	basic_shoot_2.life = 1200;
	basic_shoot_2.type_particle = 3;

	// Basic_shoot 2_up
	basic_shoot_2_up.anim.PushBack({ 58, 91, 11, 4 });
	basic_shoot_2_up.anim.PushBack({ 24, 31, 11, 12 });
	basic_shoot_2_up.anim.PushBack({ 24, 33, 11, 10 });
	basic_shoot_2_up.anim.PushBack({ 24, 35, 11, 8 });
	basic_shoot_2_up.anim.PushBack({ 24, 37, 11, 6 });
	basic_shoot_2_up.anim.PushBack({ 24, 39, 11, 4 });
	basic_shoot_2_up.anim.loop = false;
	basic_shoot_2_up.anim.speed = 0.3f;
	basic_shoot_2_up.speed.x = 8;
	basic_shoot_2_up.life = 1200;

	// Basic_shoot 2_down
	basic_shoot_2_down.anim.PushBack({ 58, 91, 11, 4 });
	basic_shoot_2_down.anim.PushBack({ 24, 39, 11, 4 });
	basic_shoot_2_down.anim.PushBack({ 24, 37, 11, 6 });
	basic_shoot_2_down.anim.PushBack({ 24, 35, 11, 8 });
	basic_shoot_2_down.anim.PushBack({ 24, 33, 11, 10 });
	basic_shoot_2_down.anim.PushBack({ 24, 31, 11, 12 });
	basic_shoot_2_down.anim.loop = false;
	basic_shoot_2_down.anim.speed = 0.3f;
	basic_shoot_2_down.speed.x = 8;
	basic_shoot_2_down.life = 1200;
	basic_shoot_2_down.type_particle = 4;


	//Basic_shoot 3_up
	basic_shoot_3_up.anim.PushBack({ 58, 92, 15, 6 });
	basic_shoot_3_up.anim.PushBack({ 22, 54, 15, 15 });
	basic_shoot_3_up.anim.PushBack({ 22, 55, 15, 14 });
	basic_shoot_3_up.anim.PushBack({ 22, 57, 15, 12 });
	basic_shoot_3_up.anim.PushBack({ 22, 59, 15, 10 });
	basic_shoot_3_up.anim.PushBack({ 22, 61, 15, 8 });
	basic_shoot_3_up.anim.PushBack({ 22, 63, 15, 6 });
	basic_shoot_3_up.anim.loop = false;
	basic_shoot_3_up.anim.speed = 0.3f;
	basic_shoot_3_up.speed.x = 8;
	basic_shoot_3_up.life = 1200;


	//Basic_shoot 3_down
	basic_shoot_3_down.anim.PushBack({ 58, 92, 15, 6 });
	basic_shoot_3_down.anim.PushBack({ 22, 63, 15, 6 });
	basic_shoot_3_down.anim.PushBack({ 22, 61, 15, 8 });
	basic_shoot_3_down.anim.PushBack({ 22, 59, 15, 10 });
	basic_shoot_3_down.anim.PushBack({ 22, 57, 15, 12 });
	basic_shoot_3_down.anim.PushBack({ 22, 55, 15, 14 });
	basic_shoot_3_down.anim.PushBack({ 22, 54, 15, 15 });
	basic_shoot_3_down.anim.loop = false;
	basic_shoot_3_down.anim.speed = 0.3f;
	basic_shoot_3_down.speed.x = 8;
	basic_shoot_3_down.life = 1200;
	basic_shoot_3_down.type_particle = 5;

	//Basic_shoot 4_up
	basic_shoot_4_up.anim.PushBack({ 58, 91, 15, 6 });
	basic_shoot_4_up.anim.PushBack({ 22, 61, 15, 8 });
	basic_shoot_4_up.anim.PushBack({ 20, 62, 17, 7 });
	basic_shoot_4_up.anim.PushBack({ 18, 62, 19, 7 });
	basic_shoot_4_up.anim.PushBack({ 16, 62, 21, 7 });
	basic_shoot_4_up.anim.PushBack({ 14, 62, 23, 7 });
	basic_shoot_4_up.anim.loop = false;
	basic_shoot_4_up.anim.speed = 0.3f;
	basic_shoot_4_up.speed.x = 8;
	basic_shoot_4_up.life = 1200;
	basic_shoot_4_up.type_particle = 6;

	//Basic_shoot 4_down
	basic_shoot_4_down.anim.PushBack({ 58, 92, 15, 6 });
	basic_shoot_4_down.anim.PushBack({ 22, 63, 15, 6 });
	basic_shoot_4_down.anim.PushBack({ 20, 62, 17, 7 });
	basic_shoot_4_down.anim.PushBack({ 18, 62, 19, 7 });
	basic_shoot_4_down.anim.PushBack({ 16, 62, 21, 7 });
	basic_shoot_4_down.anim.PushBack({ 14, 62, 23, 7 });
	basic_shoot_4_down.anim.loop = false;
	basic_shoot_4_down.anim.speed = 0.3f;
	basic_shoot_4_down.speed.x = 8;
	basic_shoot_4_down.life = 1200;
	basic_shoot_4_down.type_particle = 6;


	//Basic_shoot 5_up
	basic_shoot_5_up.anim.PushBack({ 58, 91, 16, 10 });
	basic_shoot_5_up.anim.PushBack({ 21, 94, 16, 12 });
	basic_shoot_5_up.anim.PushBack({ 19, 95, 18, 11 });
	basic_shoot_5_up.anim.PushBack({ 17, 95, 20, 11 });
	basic_shoot_5_up.anim.PushBack({ 15, 95, 22, 11 });
	basic_shoot_5_up.anim.PushBack({ 13, 95, 24, 11 });
	basic_shoot_5_up.anim.PushBack({ 11, 95, 26, 11 });
	basic_shoot_5_up.anim.loop = false;
	basic_shoot_5_up.anim.speed = 0.3f;
	basic_shoot_5_up.speed.x = 8;
	basic_shoot_5_up.life = 1200;
	basic_shoot_5_up.type_particle = 7;



	//Basic_shoot 5_down
	basic_shoot_5_down.anim.PushBack({ 58, 92, 16, 10 });
	basic_shoot_5_down.anim.PushBack({ 21, 96, 16, 10 });
	basic_shoot_5_down.anim.PushBack({ 19, 95, 18, 11 });
	basic_shoot_5_down.anim.PushBack({ 17, 95, 20, 11 });
	basic_shoot_5_down.anim.PushBack({ 15, 95, 22, 11 });
	basic_shoot_5_down.anim.PushBack({ 13, 95, 24, 11 });
	basic_shoot_5_down.anim.PushBack({ 11, 95, 26, 11 });
	basic_shoot_5_down.anim.loop = false;
	basic_shoot_5_down.anim.speed = 0.3f;
	basic_shoot_5_down.speed.x = 8;
	basic_shoot_5_down.life = 1200;
	basic_shoot_5_down.type_particle = 7;

	//Basic_shoot 6_up
	basic_shoot_6_up.anim.PushBack({ 58, 92, 16, 10 });
	basic_shoot_6_up.anim.PushBack({ 21, 84, 16, 22 });
	basic_shoot_6_up.anim.PushBack({ 21, 86, 16, 20 });
	basic_shoot_6_up.anim.PushBack({ 21, 88, 16, 18 });
	basic_shoot_6_up.anim.PushBack({ 21, 90, 16, 16 });
	basic_shoot_6_up.anim.PushBack({ 21, 92, 16, 14 });
	basic_shoot_6_up.anim.PushBack({ 21, 94, 16, 12 });
	basic_shoot_6_up.anim.PushBack({ 21, 96, 16, 10 });
	basic_shoot_6_up.anim.loop = false;
	basic_shoot_6_up.anim.speed = 0.3f;
	basic_shoot_6_up.speed.x = 8;
	basic_shoot_6_up.life = 1200;

	//Basic_shoot 6_down
	basic_shoot_6_down.anim.PushBack({ 58, 92, 16, 10 });
	basic_shoot_6_down.anim.PushBack({ 21, 96, 16, 10 });
	basic_shoot_6_down.anim.PushBack({ 21, 94, 16, 12 });
	basic_shoot_6_down.anim.PushBack({ 21, 92, 16, 14 });
	basic_shoot_6_down.anim.PushBack({ 21, 90, 16, 16 });
	basic_shoot_6_down.anim.PushBack({ 21, 88, 16, 18 });
	basic_shoot_6_down.anim.PushBack({ 21, 86, 16, 20 });
	basic_shoot_6_down.anim.PushBack({ 21, 84, 16, 22 });
	basic_shoot_6_down.anim.loop = false;
	basic_shoot_6_down.anim.speed = 0.3f;
	basic_shoot_6_down.speed.x = 8;
	basic_shoot_6_down.life = 1200;
	basic_shoot_6_down.type_particle = 8;


	// Laser 0
	laser_0.anim.PushBack({ 57, 16, 16, 3 });
	laser_0.anim.loop = false;
	laser_0.anim.speed = 0.3f;
	laser_0.speed.x = 8;
	laser_0.life = 1200;

	// Laser 1 up
	laser_1.anim.PushBack({ 57, 35, 16, 18 });
	laser_1.anim.loop = false;
	laser_1.anim.speed = 0.3f;
	laser_1.speed.x = 8;
	laser_1.speed.y = -7;
	laser_1.life = 1200;

	// Laser 1 down
	laser_1_5.anim.PushBack({ 57, 60, 16, 18 });
	laser_1_5.anim.loop = false;
	laser_1_5.anim.speed = 0.3f;
	laser_1_5.speed.x = 8;
	laser_1_5.speed.y = 7;
	laser_1_5.life = 1200;

	// Laser 2 up
	laser_2.anim.PushBack({ 57, 60, 16, 18 });
	laser_2.anim.loop = false;
	laser_2.anim.speed = 0.3f;
	laser_2.speed.x = -6;
	laser_2.speed.y = -7;
	laser_2.life = 1200;

	// Laser 2 down
	laser_2_5.anim.PushBack({ 57, 35, 16, 18 });
	laser_2_5.anim.loop = false;
	laser_2_5.anim.speed = 0.3f;
	laser_2_5.speed.x = -6;
	laser_2_5.speed.y = 7;
	laser_2_5.life = 1200;

	// Laser 3 up
	laser_3_up.anim.PushBack({ 76, 2, 16, 22 });
	laser_3_up.anim.PushBack({ 76, 65, 16, 22 });
	laser_3_up.anim.loop = true;
	laser_3_up.anim.speed = 0.3f;
	laser_3_up.speed.x = 8;
	laser_3_up.speed.y = -7;
	laser_3_up.life = 1200;

	// Laser 3 down
	laser_3_down.anim.PushBack({ 76, 32, 16, 22 });
	laser_3_down.anim.PushBack({ 76, 95, 16, 22 });
	laser_3_down.anim.loop = true;
	laser_3_down.anim.speed = 0.3f;
	laser_3_down.speed.x = 8;
	laser_3_down.speed.y = 7;
	laser_3_down.life = 1200;

	// Laser 3 up back
	laser_3_up_back.anim.PushBack({ 76, 32, 16, 22 });
	laser_3_up_back.anim.PushBack({ 76, 95, 16, 22 });
	laser_3_up_back.anim.loop = true;
	laser_3_up_back.anim.speed = 0.3f;
	laser_3_up_back.speed.x = -6;
	laser_3_up_back.speed.y = -7;
	laser_3_up_back.life = 1200;

	// Laser 3 down back
	laser_3_down_back.anim.PushBack({ 76, 2, 16, 22 });
	laser_3_down_back.anim.PushBack({ 76, 65, 16, 22 });
	laser_3_down_back.anim.loop = true;
	laser_3_down_back.anim.speed = 0.3f;
	laser_3_down_back.speed.x = -6;
	laser_3_down_back.speed.y = 7;
	laser_3_down_back.life = 1200;

	// Laser 4 up
	laser_4_up.anim.PushBack({ 129, 0, 31, 31 });
	laser_4_up.anim.PushBack({ 166, 0, 31, 31 });
	laser_4_up.anim.loop = true;
	laser_4_up.anim.speed = 0.3f;
	laser_4_up.speed.x = 8;
	laser_4_up.speed.y = -7;
	laser_4_up.life = 1200;

	// Laser 4 down
	laser_4_down.anim.PushBack({ 129, 32, 31, 31 });
	laser_4_down.anim.PushBack({ 166, 32, 31, 31 });
	laser_4_down.anim.loop = true;
	laser_4_down.anim.speed = 0.3f;
	laser_4_down.speed.x = 8;
	laser_4_down.speed.y = 7;
	laser_4_down.life = 1200;

	// Laser 4 up back
	laser_4_up_back.anim.PushBack({ 129, 96, 31, 31 });
	laser_4_up_back.anim.PushBack({ 166, 96, 31, 31 });
	laser_4_up_back.anim.loop = true;
	laser_4_up_back.anim.speed = 0.2f;
	laser_4_up_back.speed.x = -6;
	laser_4_up_back.speed.y = -7;
	laser_4_up_back.life = 1200;

	// Laser 4 down back
	laser_4_down_back.anim.PushBack({ 129, 64, 31, 31 });
	laser_4_down_back.anim.PushBack({ 166, 64, 31, 31 });
	laser_4_down_back.anim.loop = true;
	laser_4_down_back.anim.speed = 0.2f;
	laser_4_down_back.speed.x = -6;
	laser_4_down_back.speed.y = 7;
	laser_4_down_back.life = 1200;

	// Laser 5 up
	laser_5_up.anim.PushBack({ 94, 0, 31, 31 });

	laser_5_up.anim.loop = true;
	laser_5_up.anim.speed = 0.3f;
	laser_5_up.speed.x = 8;
	laser_5_up.speed.y = -7;
	laser_5_up.life = 1200;

	// Laser 5 down
	laser_5_down.anim.PushBack({ 94, 32, 31, 31 });

	laser_5_down.anim.loop = true;
	laser_5_down.anim.speed = 0.3f;
	laser_5_down.speed.x = 8;
	laser_5_down.speed.y = 7;
	laser_5_down.life = 1200;

	// Laser 5 up back

	laser_5_up_back.anim.PushBack({ 94, 96, 31, 31 });
	laser_5_up_back.anim.loop = true;
	laser_5_up_back.anim.speed = 0.2f;
	laser_5_up_back.speed.x = -6;
	laser_5_up_back.speed.y = -7;
	laser_5_up_back.life = 1200;

	// Laser 5 down back

	laser_5_down_back.anim.PushBack({ 94, 64, 31, 31 });
	laser_5_down_back.anim.loop = true;
	laser_5_down_back.anim.speed = 0.2f;
	laser_5_down_back.speed.x = -6;
	laser_5_down_back.speed.y = 7;
	laser_5_down_back.life = 1200;

	// Laser 5 up
	laser_5_up.anim.PushBack({ 94, 0, 31, 31 });

	laser_5_up.anim.loop = true;
	laser_5_up.anim.speed = 0.3f;
	laser_5_up.speed.x = 8;
	laser_5_up.speed.y = -7;
	laser_5_up.life = 1200;

	// Laser 5 down
	laser_5_down.anim.PushBack({ 94, 32, 31, 31 });

	laser_5_down.anim.loop = true;
	laser_5_down.anim.speed = 0.3f;
	laser_5_down.speed.x = 8;
	laser_5_down.speed.y = 7;
	laser_5_down.life = 1200;

	// Laser 5 up back

	laser_5_up_back.anim.PushBack({ 94, 96, 31, 31 });
	laser_5_up_back.anim.loop = true;
	laser_5_up_back.anim.speed = 0.2f;
	laser_5_up_back.speed.x = -6;
	laser_5_up_back.speed.y = -7;
	laser_5_up_back.life = 1200;

	// Laser 5 down back

	laser_5_down_back.anim.PushBack({ 94, 64, 31, 31 });
	laser_5_down_back.anim.loop = true;
	laser_5_down_back.anim.speed = 0.2f;
	laser_5_down_back.speed.x = -6;
	laser_5_down_back.speed.y = 7;
	laser_5_down_back.life = 1200;



	// Laser 6 up
	laser_6_up.anim.PushBack({ 205, 0, 47, 47 });

	laser_6_up.anim.loop = true;
	laser_6_up.anim.speed = 0.3f;
	laser_6_up.speed.x = 8;
	laser_6_up.speed.y = -7;
	laser_6_up.life = 1200;

	// Laser 6 down
	laser_6_down.anim.PushBack({ 205, 48, 47, 47 });

	laser_6_down.anim.loop = true;
	laser_6_down.anim.speed = 0.3f;
	laser_6_down.speed.x = 8;
	laser_6_down.speed.y = 7;
	laser_6_down.life = 1200;

	// Laser 6 up back 

	laser_6_up_back.anim.PushBack({ 205, 144, 47, 47 });
	laser_6_up_back.anim.loop = true;
	laser_6_up_back.anim.speed = 0.2f;
	laser_6_up_back.speed.x = -6;
	laser_6_up_back.speed.y = -7;
	laser_6_up_back.life = 1200;

	// Laser 6 down back

	laser_6_down_back.anim.PushBack({ 205, 96, 47, 47 });
	laser_6_down_back.anim.loop = true;
	laser_6_down_back.anim.speed = 0.2f;
	laser_6_down_back.speed.x = -6;
	laser_6_down_back.speed.y = 7;
	laser_6_down_back.life = 1200;

	//BACK_SHOT

	//Disparo_trasero_0
	back_shoot_0.anim.PushBack({ 6, 69, 10, 3 });
	back_shoot_0.anim.loop = false;
	back_shoot_0.anim.speed = 0.3f;
	back_shoot_0.speed.x = 8;
	back_shoot_0.life = 1200;

	//Disparo_trasero_0_back
	back_shoot_0_back.anim.PushBack({ 6, 84, 10, 3 });
	back_shoot_0_back.anim.loop = false;
	back_shoot_0_back.anim.speed = 0.3f;
	back_shoot_0_back.speed.x = -8;
	back_shoot_0_back.life = 1200;

	// Back shoot 2 diagonal up
	back_shoot_2_diagonal_up.anim.PushBack({ 54, 110, 10, 7 });
	back_shoot_2_diagonal_up.anim.loop = false;
	back_shoot_2_diagonal_up.anim.speed = 0.3f;
	back_shoot_2_diagonal_up.speed.x = -4;
	back_shoot_2_diagonal_up.speed.y = -3;
	back_shoot_2_diagonal_up.life = 1200;

	// Back shoot 2 diagonal down
	back_shoot_2_diagonal_down.anim.PushBack({ 54, 119, 10, 7 });
	back_shoot_2_diagonal_down.anim.loop = false;
	back_shoot_2_diagonal_down.anim.speed = 0.3f;
	back_shoot_2_diagonal_down.speed.x = -4;
	back_shoot_2_diagonal_down.speed.y = 3;
	back_shoot_2_diagonal_down.life = 1200;

	// Back shoot 3 back
	back_shoot_3_back.anim.PushBack({ 3, 23, 15, 5 });
	back_shoot_3_back.anim.loop = false;
	back_shoot_3_back.anim.speed = 0.3f;
	back_shoot_3_back.speed.x = -8;
	back_shoot_3_back.life = 1200;

	// Back shoot 3 diagonal up 
	back_shoot_3_diagonal_up.anim.PushBack({ 5, 50, 11, 8 });
	back_shoot_3_diagonal_up.anim.loop = false;
	back_shoot_3_diagonal_up.anim.speed = 0.3f;
	back_shoot_3_diagonal_up.speed.x = -4;
	back_shoot_3_diagonal_up.speed.y = -3;
	back_shoot_3_diagonal_up.life = 1200;

	// Back shoot 3 diagonal down
	back_shoot_3_diagonal_down.anim.PushBack({ 5, 37, 11, 8 });
	back_shoot_3_diagonal_down.anim.loop = false;
	back_shoot_3_diagonal_down.anim.speed = 0.3f;
	back_shoot_3_diagonal_down.speed.x = -4;
	back_shoot_3_diagonal_down.speed.y = 3;
	back_shoot_3_diagonal_down.life = 1200;

	//Disparo_trasero_0_up
	back_shoot_0_up.anim.PushBack({ 6, 150, 10, 3 });
	//back_shoot_0_up.anim.PushBack({ 6, 59, 10, 13 });
	back_shoot_0_up.anim.PushBack({ 6, 61, 10, 11 });
	back_shoot_0_up.anim.PushBack({ 6, 63, 10, 9 });
	back_shoot_0_up.anim.PushBack({ 6, 65, 10, 7 });
	back_shoot_0_up.anim.PushBack({ 6, 67, 10, 5 });
	back_shoot_0_up.anim.PushBack({ 6, 69, 10, 3 });
	back_shoot_0_up.anim.loop = false;
	back_shoot_0_up.anim.speed = 0.3f;
	back_shoot_0_up.speed.x = 8;
	back_shoot_0_up.life = 1200;



	//Disparo_trasero_0_down
	back_shoot_0_down.anim.PushBack({ 6, 150, 10, 3 });
	back_shoot_0_down.anim.PushBack({ 6, 69, 10, 3 });
	back_shoot_0_down.anim.PushBack({ 6, 67, 10, 5 });
	back_shoot_0_down.anim.PushBack({ 6, 65, 10, 7 });
	back_shoot_0_down.anim.PushBack({ 6, 63, 10, 9 });
	back_shoot_0_down.anim.PushBack({ 6, 61, 10, 11 });
	//	back_shoot_0_down.anim.PushBack({ 6, 59, 10, 13 });
	back_shoot_0_down.anim.loop = false;
	back_shoot_0_down.anim.speed = 0.3f;
	back_shoot_0_down.speed.x = 8;
	back_shoot_0_down.life = 1200;
	back_shoot_0_down.type_particle = 9;

	//Disparo_trasero_0_5 (avanzado)
	back_shoot_0_5.anim.PushBack({ 6, 150, 10, 3 });
	back_shoot_0_5.anim.PushBack({ 4, 69, 12, 3 });
	back_shoot_0_5.anim.PushBack({ 2, 69, 14, 3 });
	back_shoot_0_5.anim.PushBack({ 0, 69, 16, 3 });
	back_shoot_0_5.anim.loop = false;
	back_shoot_0_5.anim.speed = 0.3f;
	back_shoot_0_5.speed.x = 8;
	back_shoot_0_5.life = 1200;
	back_shoot_0_5.type_particle = 10;

	//Disparo_trasero_1_5 (avanzado)
	back_shoot_1_5.anim.PushBack({ 6, 150, 15, 5 });
	back_shoot_1_5.anim.PushBack({ 3, 8, 15, 5 });
	back_shoot_1_5.anim.PushBack({ 1, 8, 17, 5 });
	back_shoot_1_5.anim.PushBack({ 0, 8, 18, 5 });
	back_shoot_1_5.anim.loop = false;
	back_shoot_1_5.anim.speed = 0.3f;
	back_shoot_1_5.speed.x = 8;
	back_shoot_1_5.life = 1200;
	back_shoot_1_5.type_particle = 11;

	//normal & power-up 1
	// Helix_01_1
	helix_01_1.anim.PushBack({ 41, 9, 13, 6 });
	helix_01_1.anim.PushBack({ 41, 23, 13, 6 });
	helix_01_1.anim.loop = false;
	helix_01_1.anim.speed = 0.3f;
	helix_01_1.speed.x = 8;
	helix_01_1.speed.y = 1;
	helix_01_1.life = 1200;

	// Helix_01_2
	helix_01_2.anim.PushBack({ 41, 9, 13, 6 });
	helix_01_2.anim.PushBack({ 41, 23, 13, 6 });
	helix_01_2.anim.loop = false;
	helix_01_2.anim.speed = 0.3f;
	helix_01_2.speed.x = 8;
	helix_01_2.speed.y = -1;
	helix_01_2.life = 1200;

	// Helix 01_3
	helix_01_3.anim.PushBack({ 41, 9, 13, 6 });
	helix_01_3.anim.PushBack({ 41, 23, 13, 6 });
	helix_01_3.anim.loop = false;
	helix_01_3.anim.speed = 0.3f;
	helix_01_3.speed.x = 8;
	helix_01_3.speed.y = 0;
	helix_01_3.life = 1200;

	//power-up 2
	// Helix 02_1
	helix_02_1.anim.PushBack({ 41, 8, 13, 8 });
	helix_02_1.anim.PushBack({ 41, 22, 13, 8 });
	helix_02_1.anim.PushBack({ 41, 38, 13, 8 });
	helix_02_1.anim.loop = false;
	helix_02_1.anim.speed = 0.3f;
	helix_02_1.speed.x = 8;
	helix_02_1.speed.y = 1;
	helix_02_1.life = 1200;

	// Helix 02_2
	helix_02_2.anim.PushBack({ 41, 8, 13, 8 });
	helix_02_2.anim.PushBack({ 41, 22, 13, 8 });
	helix_02_2.anim.PushBack({ 41, 38, 13, 8 });
	helix_02_2.anim.loop = false;
	helix_02_2.anim.speed = 0.3f;
	helix_02_2.speed.x = 8;
	helix_02_2.speed.y = -1;
	helix_02_2.life = 1200;

	// Helix 02_3
	helix_02_3.anim.PushBack({ 41, 8, 13, 8 });
	helix_02_3.anim.PushBack({ 41, 22, 13, 8 });
	helix_02_3.anim.PushBack({ 41, 38, 13, 8 });
	helix_02_3.anim.loop = false;
	helix_02_3.anim.speed = 0.3f;
	helix_02_3.speed.x = 8;
	helix_02_3.speed.y = 0;
	helix_02_3.life = 1200;

	// Power-up 3
	// Helix 03_1
	helix_03_1.anim.PushBack({ 41, 8, 13, 8 });
	helix_03_1.anim.PushBack({ 41, 22, 13, 8 });
	helix_03_1.anim.PushBack({ 41, 38, 13, 8 });
	helix_03_1.anim.loop = false;
	helix_03_1.anim.speed = 0.3f;
	helix_03_1.speed.x = 8;
	helix_03_1.speed.y = 2;
	helix_03_1.life = 1200;

	// Helix 03_2
	helix_03_2.anim.PushBack({ 41, 8, 13, 8 });
	helix_03_2.anim.PushBack({ 41, 22, 13, 8 });
	helix_03_2.anim.PushBack({ 41, 38, 13, 8 });
	helix_03_2.anim.loop = false;
	helix_03_2.anim.speed = 0.3f;
	helix_03_2.speed.x = 8;
	helix_03_2.speed.y = -2;
	helix_03_2.life = 1200;

	// Power-up 4 
	// Helix 04_1
	helix_04_1.anim.PushBack({ 41, 8, 13, 8 });
	helix_04_1.anim.PushBack({ 41, 22, 13, 8 });
	helix_04_1.anim.PushBack({ 41, 38, 13, 8 });
	helix_04_1.anim.PushBack({ 41, 49, 13, 12 });
	helix_04_1.anim.loop = false;
	helix_04_1.anim.speed = 0.3f;
	helix_04_1.speed.x = 8;
	helix_04_1.speed.y = 1;
	helix_04_1.life = 1200;

	// Helix 04_2
	helix_04_2.anim.PushBack({ 41, 8, 13, 8 });
	helix_04_2.anim.PushBack({ 41, 22, 13, 8 });
	helix_04_2.anim.PushBack({ 41, 38, 13, 8 });
	helix_04_2.anim.PushBack({ 41, 49, 13, 12 });
	helix_04_2.anim.loop = false;
	helix_04_2.anim.speed = 0.3f;
	helix_04_2.speed.x = 8;
	helix_04_2.speed.y = -1;
	helix_04_2.life = 1200;

	// Power up 5 //
	// Helix 05_3
	helix_05_3.anim.PushBack({ 41, 8, 13, 8 });
	helix_05_3.anim.PushBack({ 41, 22, 13, 8 });
	helix_05_3.anim.PushBack({ 41, 38, 13, 8 });
	helix_05_2.anim.PushBack({ 41, 49, 13, 12 });
	helix_05_3.anim.PushBack({ 41, 64, 13, 14 });
	helix_05_3.anim.loop = false;
	helix_05_3.anim.speed = 0.3f;
	helix_05_3.speed.x = 8;
	helix_05_3.speed.y = 0;
	helix_05_3.life = 1200;

	// Helix 05_1
	helix_05_1.anim.PushBack({ 41, 8, 13, 8 });
	helix_05_1.anim.PushBack({ 41, 22, 13, 8 });
	helix_05_1.anim.PushBack({ 41, 38, 13, 8 });
	helix_05_1.anim.PushBack({ 41, 49, 13, 12 });
	helix_05_1.anim.PushBack({ 41, 64, 13, 14 });
	helix_05_1.anim.loop = false;
	helix_05_1.anim.speed = 0.3f;
	helix_05_1.speed.x = 8;
	helix_05_1.speed.y = 1;
	helix_05_1.life = 1200;

	// Helix 05_2
	helix_05_2.anim.PushBack({ 41, 8, 13, 8 });
	helix_05_2.anim.PushBack({ 41, 22, 13, 8 });
	helix_05_2.anim.PushBack({ 41, 38, 13, 8 });
	helix_05_2.anim.PushBack({ 41, 49, 13, 12 });
	helix_05_2.anim.PushBack({ 41, 64, 13, 14 });
	helix_05_2.anim.loop = false;
	helix_05_2.anim.speed = 0.3f;
	helix_05_2.speed.x = 8;
	helix_05_2.speed.y = -1;
	helix_05_2.life = 1200;

	// Power-up 6 
	// Helix 06_1
	helix_06_1.anim.PushBack({ 41, 8, 13, 8 });
	helix_06_1.anim.PushBack({ 41, 22, 13, 8 });
	helix_06_1.anim.PushBack({ 41, 38, 13, 8 });
	helix_06_1.anim.PushBack({ 41, 49, 13, 12 });
	helix_06_1.anim.PushBack({ 41, 64, 13, 14 });
	helix_06_1.anim.loop = false;
	helix_06_1.anim.speed = 0.3f;
	helix_06_1.speed.x = 8;
	helix_06_1.speed.y = 2;
	helix_06_1.life = 1200;

	// Helix 06_2
	helix_06_2.anim.PushBack({ 41, 8, 13, 8 });
	helix_06_2.anim.PushBack({ 41, 22, 13, 8 });
	helix_06_2.anim.PushBack({ 41, 38, 13, 8 });
	helix_06_2.anim.PushBack({ 41, 49, 13, 12 });
	helix_06_2.anim.PushBack({ 41, 64, 13, 14 });
	helix_06_2.anim.loop = false;
	helix_06_2.anim.speed = 0.3f;
	helix_06_2.speed.x = 8;
	helix_06_2.speed.y = -2;
	helix_06_2.life = 1200;



	// Explosion ship
	explosion.anim.PushBack({ 33, 19, 35, 35 });
	explosion.anim.PushBack({ 82, 18, 35, 35 });
	explosion.anim.PushBack({ 134, 19, 35, 35 });
	explosion.anim.PushBack({ 187, 19, 35, 35 });
	explosion.anim.PushBack({ 33, 55, 35, 35 });
	explosion.anim.PushBack({ 82, 56, 35, 35 });
	explosion.anim.PushBack({ 134, 55, 35, 35 });
	explosion.anim.PushBack({ 187, 54, 35, 35 });
	explosion.anim.PushBack({ 7, 95, 35, 35 });
	explosion.anim.PushBack({ 50, 95, 35, 35 });
	explosion.anim.PushBack({ 87, 95, 35, 35 });
	explosion.anim.PushBack({ 118, 95, 35, 35 });
	explosion.anim.PushBack({ 148, 95, 35, 35 });
	explosion.anim.PushBack({ 177, 95, 35, 35 });
	explosion.anim.PushBack({ 204, 95, 35, 35 });
	explosion.anim.PushBack({ 228, 95, 28, 35 });
	explosion.anim.loop = false;
	explosion.anim.speed = 0.7f;
	explosion.Type = explosion.EXPLOSION;

	//Explosion 2nd player ship
	explosion2.anim.PushBack({ 45, 143, 35, 35 });
	explosion2.anim.PushBack({ 82, 142, 35, 31 });
	explosion2.anim.PushBack({ 122, 140, 35, 33 });
	explosion2.anim.PushBack({ 162, 139, 35, 34 });
	explosion2.anim.PushBack({ 48, 174, 35, 35 });
	explosion2.anim.PushBack({ 89, 172, 35, 35 });
	explosion2.anim.PushBack({ 132, 173, 35, 35 });
	explosion2.anim.PushBack({ 187, 54, 35, 35 });
	explosion2.anim.PushBack({ 7, 95, 35, 35 });
	explosion2.anim.PushBack({ 50, 95, 35, 35 });
	explosion2.anim.PushBack({ 87, 95, 35, 35 });
	explosion2.anim.PushBack({ 118, 95, 35, 35 });
	explosion2.anim.PushBack({ 148, 95, 35, 35 });
	explosion2.anim.PushBack({ 177, 95, 35, 35 });
	explosion2.anim.PushBack({ 204, 95, 35, 35 });
	explosion2.anim.PushBack({ 228, 95, 28, 35 });
	explosion2.anim.loop = false;
	explosion2.anim.speed = 0.7f;
	explosion2.Type = explosion.EXPLOSION;

	//1st Explosion enemy
	enemy_explosion1.anim.PushBack({ 4, 12, 39, 30 });
	enemy_explosion1.anim.PushBack({ 26, 11, 39, 38 });
	enemy_explosion1.anim.PushBack({ 63, 11, 39, 38 });
	enemy_explosion1.anim.PushBack({ 103, 11, 39, 38 });
	enemy_explosion1.anim.PushBack({ 142, 11, 39, 38 });
	enemy_explosion1.anim.PushBack({ 183, 11, 39, 38 });
	enemy_explosion1.anim.PushBack({ 11, 52, 39, 38 });
	enemy_explosion1.anim.PushBack({ 58, 52, 39, 38 });
	enemy_explosion1.anim.PushBack({ 108, 52, 39, 38 });
	enemy_explosion1.anim.PushBack({ 153, 52, 39, 38 });
	enemy_explosion1.anim.loop = false;
	enemy_explosion1.anim.speed = 0.6f;
	enemy_explosion1.Type = explosion.EXPLOSION_ENEMY;

	//2nd Explosion enemy
	enemy_explosion2.anim.PushBack({ 6, 100, 39, 38 });
	enemy_explosion2.anim.PushBack({ 38, 100, 39, 38 });
	enemy_explosion2.anim.PushBack({ 72, 100, 39, 38 });
	enemy_explosion2.anim.PushBack({ 117, 99, 39, 38 });
	enemy_explosion2.anim.PushBack({ 160, 98, 39, 38 });
	enemy_explosion2.anim.PushBack({ 203, 99, 39, 38 });
	enemy_explosion2.anim.PushBack({ 10, 138, 39, 38 });
	enemy_explosion2.anim.PushBack({ 47, 138, 39, 38 });
	enemy_explosion2.anim.PushBack({ 84, 138, 39, 38 });
	enemy_explosion2.anim.PushBack({ 122, 138, 39, 38 });
	enemy_explosion2.anim.PushBack({ 160, 138, 39, 38 });
	enemy_explosion2.anim.PushBack({ 197, 138, 39, 38 });
	enemy_explosion2.anim.PushBack({ 8, 178, 39, 38 });
	enemy_explosion2.anim.PushBack({ 42, 178, 39, 38 });
	enemy_explosion2.anim.PushBack({ 73, 178, 39, 38 });
	enemy_explosion2.anim.loop = false;
	enemy_explosion2.anim.speed = 0.7f;
	enemy_explosion2.Type = explosion.EXPLOSION_ENEMY;

	//3rd explosion enemy
	enemy_explosion2.anim.PushBack({ 112, 217, 24, 24 });
	enemy_explosion2.anim.PushBack({ 139, 217, 24, 24 });
	enemy_explosion2.anim.PushBack({ 168, 217, 24, 24 });
	enemy_explosion2.anim.PushBack({ 205, 217, 24, 24 });
	enemy_explosion2.anim.PushBack({ 14, 105, 24, 24 });
	enemy_explosion3.anim.loop = false;
	enemy_explosion3.anim.speed = 0.5f;
	enemy_explosion3.Type = explosion.EXPLOSION_ENEMY;

	//Enemy15 shot
	enemy15shot.anim.PushBack({ 84, 10, 53, 29 });
	enemy15shot.anim.PushBack({ 139, 10, 54, 29 });
	enemy15shot.anim.PushBack({ 30, 44, 56, 29 });
	enemy15shot.anim.PushBack({ 91, 44, 58, 29 });
	enemy15shot.anim.loop = false;
	enemy15shot.speed.x = -2;
	enemy15shot.speed.y = 0;
	enemy15shot.life = 2500;*/
}

j1Particles::~j1Particles()
{}

// Load assets
bool j1Particles::Start()
{
	/*LOG("Loading particles");
	graphics = App->textures->Load("Images/Ship/laser_types.png");
	graphics2 = App->textures->Load("Images/Ship/ship-explosion.png");
	graphics3 = App->textures->Load("Images/Enemies/explosions_all_in_one.png");
	enemy15shotgraphics = App->textures->Load("Images/Enemies/15.png");
	*/


	return true;
}


// Unload assets
bool j1Particles::CleanUp()
{
	/*LOG("Unloading particles");
	App->textures->Unload(graphics);
	App->textures->Unload(graphics2);
	App->textures->Unload(graphics3);
	App->textures->Unload(enemy15shotgraphics);*/

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
bool j1Particles::Update(float dt)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if (SDL_GetTicks() >= p->born)
		{
			switch (p->Type) {
			/*case p->EXPLOSION:
				App->render->Blit(graphics2, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				break;

			case p->EXPLOSION_ENEMY:
				App->render->Blit(graphics3, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				break;
			case p->SHOOT:

				App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				break;

			case p->SHOOT_ENEMY:

				App->render->Blit(enemy15shotgraphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				break;*/

			}

			if (p->fx_played == false)
			{
				p->fx_played = true;
			}
		}
	}

	return true;
}

void j1Particles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			p->Type = particle.Type;
			if (collider_type != COLLIDER_NONE) {
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
				p->collider->type_collider = particle.type_particle;

			}
			active[i] = p;
			break;
		}
	}
}

// TODO 5: Make so every time a particle hits a wall it triggers an explosion particle
void j1Particles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			//code
			//App->particles->AddParticle(App->particles->explosion, active[i]->position.x, active[i]->position.y);

			//active[i]->collider->to_delete = true;

			delete active[i];
			active[i] = nullptr;
			break;
		}
	}
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) :
	anim(p.anim), position(p.position), speed(p.speed),
	fx(p.fx), born(p.born), life(p.life)
{}

Particle::~Particle()
{
	if (collider != nullptr) {

		collider->to_delete = true;

	}
}

bool Particle::Update()
{
	bool ret = true;



	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if (anim.Finished())
			ret = false;

	/*position.x += speed.x;
	position.y += speed.y;

	if (collider != nullptr) {
		if (position.y < App->render->camera.y / SCREEN_SIZE || position.x < App->render->camera.x / SCREEN_SIZE || position.x > App->render->camera.x / SCREEN_SIZE + SCREEN_WIDTH - collider->rect.w || position.y > App->render->camera.y / SCREEN_SIZE + SCREEN_WIDTH - collider->rect.h)
		{
			ret = false;
			return ret;
		}
	}*/

	/*if (collider != nullptr) {
		collider->SetPos(position.x, position.y);
		if (collider->type_collider == 1)
			collider->SetPos(position.x, position.y + 2);
		if (collider->type_collider == 2)
			collider->SetPos(position.x, position.y + 4);
		if (collider->type_collider == 3)
			collider->SetPos(position.x + 6, position.y);
		if (collider->type_collider == 4)
			collider->SetPos(position.x, position.y + 8);
		if (collider->type_collider == 5)
			collider->SetPos(position.x, position.y + 9);
		if (collider->type_collider == 6)
			collider->SetPos(position.x + 8, position.y + 1);
		if (collider->type_collider == 7)
			collider->SetPos(position.x + 10, position.y + 1);
		if (collider->type_collider == 8)
			collider->SetPos(position.x, position.y + 12);
		if (collider->type_collider == 9)
			collider->SetPos(position.x, position.y + 8);
		if (collider->type_collider == 10)
			collider->SetPos(position.x + 6, position.y);
		if (collider->type_collider == 11)
			collider->SetPos(position.x + 3, position.y);
			

	}*/

	return ret;
}



