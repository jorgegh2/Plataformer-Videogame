//#include "Globals.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Input.h"
//#include "ModulePlayersMenu.h"
//#include "ModuleRender.h"
#include "j1Player.h"
//#include "SDL\include\SDL.h"
//#include "ModuleParticles.h"
//#include "ModuleCollision.h"
//#include "ModuleFadeToBlack.h"
//#include "Level01.h"
//#include "ModuleGameOver.h"
//#include "ModuleGameIntroduction.h"
//#include "ModuleAudio.h"
//#include "ModuleFonts.h"
//#include "UI.h"
//#include "ModulePowerUp.h"
#include "p2Log.h"


#include "j1Render.h"



j1Player::j1Player() : j1Module()
{
	graphics = NULL;
	current_animation = NULL;

	//------ New Animations Awesome Game 2 ------

	// IDLE

	idle.PushBack({ 34, 16, 155, 171 });
	idle.PushBack({ 230, 16, 155, 171 });
	idle.PushBack({ 441, 17, 156, 170 });
	idle.PushBack({ 640, 18, 156, 169 });
	idle.PushBack({ 838, 18, 157, 169 });
	idle.PushBack({ 1043, 18, 157, 169 });
	idle.PushBack({ 1235, 18, 156, 169 });
	idle.PushBack({ 1422, 17, 156, 170 });
	idle.PushBack({ 1609, 16, 155, 171 });
	idle.PushBack({ 1785, 16, 155, 171 });
	idle.loop = true;
	idle.speed = 0.01f;

	// ALERT

	alert.PushBack({ 34, 264, 155, 171 });
	alert.PushBack({ 257, 263, 154, 172 });
	alert.PushBack({ 460, 261, 152, 174 });
	alert.PushBack({ 653, 260, 152, 175 });
	alert.PushBack({ 853, 260, 152, 175 });
	alert.PushBack({ 1059, 260, 152, 175 });
	alert.PushBack({ 1257, 260, 152, 175 });
	alert.PushBack({ 1437, 261, 152, 174 });
	alert.PushBack({ 1612, 263, 154, 172 });
	alert.PushBack({ 1788, 264, 155, 171 });
	alert.loop = true;
	alert.speed = 0.8f;

	// WALK

	walk.PushBack({ 44, 772, 154, 171 });
	walk.PushBack({ 281, 772, 155, 171 });
	walk.PushBack({ 476, 772, 155, 171 });
	walk.PushBack({ 660, 773, 156, 169 });
	walk.PushBack({ 856, 773, 156, 169 });
	walk.PushBack({ 1046, 773, 156, 169 });
	walk.PushBack({ 1262, 773, 156, 169 });
	walk.PushBack({ 1444, 772, 155, 171 });
	walk.PushBack({ 1622, 772, 155, 171 });
	walk.PushBack({ 1797, 772, 154, 171 });
	walk.loop = true;
	walk.speed = 0.8f;


	// RUN

	run.PushBack({ 51, 1016, 143, 184 });
	run.PushBack({ 285, 1018, 144, 182 });
	run.PushBack({ 479, 1021, 148, 179 });
	run.PushBack({ 668, 1024, 151, 175 });
	run.PushBack({ 862, 1027, 154, 172 });
	run.PushBack({ 1061, 1027, 154, 172 });
	run.PushBack({ 1281, 1024, 151, 175 });
	run.PushBack({ 1467, 1021, 148, 179 });
	run.PushBack({ 1640, 1018, 144, 182 });
	run.PushBack({ 1816, 1016, 143, 184 });
	run.loop = true;
	run.speed = 0.8f;


	// JUMP

	jump.PushBack({ 39, 1332, 151, 175 });
	jump.PushBack({ 275, 1327, 150, 177 });
	jump.PushBack({ 488, 1320, 141, 185 });
	jump.PushBack({ 695, 1317, 134, 191 });
	jump.PushBack({ 881, 1310, 145, 182 });
	jump.PushBack({ 1063, 1299, 158, 167 });
	jump.PushBack({ 1251, 1296, 165, 156 });
	jump.PushBack({ 1444, 1305, 160, 160 });
	jump.PushBack({ 1627, 1322, 157, 168 });
	jump.PushBack({ 1813, 1332, 155, 171 });
	jump.loop = true;
	jump.speed = 0.8f;


	// SHOOT

	shot.PushBack({ 49, 521, 155, 171 });
	shot.PushBack({ 269, 525, 158, 171 });
	shot.PushBack({ 460, 531, 160, 161 });
	shot.PushBack({ 635, 537, 162, 155 });
	shot.PushBack({ 834, 542, 163, 150 });
	shot.PushBack({ 1041, 544, 163, 148 });
	shot.PushBack({ 1241, 544, 163, 148 });
	shot.PushBack({ 1423, 539, 163, 153 });
	shot.PushBack({ 1610, 529, 159, 165 });
	shot.PushBack({ 1791, 521, 155, 171 });
	shot.loop = true;
	shot.speed = 0.8f;



	// HIT

	hit.PushBack({ 41, 1587, 157, 169 });
	hit.PushBack({ 267, 1588, 157, 168 });
	hit.PushBack({ 467, 1589, 157, 168 });
	hit.PushBack({ 665, 1591, 158, 166 });
	hit.PushBack({ 870, 1593, 159, 166 });
	hit.PushBack({ 1075, 1593, 159, 166 });
	hit.PushBack({ 1284, 1591, 158, 166 });
	hit.PushBack({ 1528, 1589, 157, 168 });
	hit.PushBack({ 1777, 1588, 155, 168 });
	hit.PushBack({ 2037, 1588, 155, 168 });
	hit.loop = true;
	hit.speed = 0.8f;


	// DIE

	die.PushBack({ 44, 1879, 156, 169 });
	die.PushBack({ 245, 1889, 161, 160 });
	die.PushBack({ 431, 1900, 163, 150 });
	die.PushBack({ 616, 1901, 164, 149 });
	die.PushBack({ 807, 1903, 164, 147 });
	die.PushBack({ 1003, 1905, 164, 143 });
	die.PushBack({ 1202, 1910, 179, 136 });
	die.PushBack({ 1417, 1914, 196, 133 });
	die.PushBack({ 1643, 1943, 174, 151 });
	die.PushBack({ 1860, 1955, 151, 174 });
	die.loop = true;
	die.speed = 0.8f;

	//-------------------------------------

	/*// Idle animation
	idle.PushBack({ 94, 108, SHIP_WIDTH, SHIP_HEIGHT });

	// Up animation
	up.PushBack({ 94, 87, SHIP_WIDTH, SHIP_HEIGHT });
	up.PushBack({ 94, 66, SHIP_WIDTH, SHIP_HEIGHT });
	up.loop = false;
	up.speed = 0.1f;

	upback.PushBack({ 94, 87, SHIP_WIDTH, SHIP_HEIGHT });
	upback.PushBack({ 94, 108, SHIP_WIDTH, SHIP_HEIGHT });
	upback.loop = false;
	upback.speed = 0.1f;

	// Down animation
	down.PushBack({ 94, 131, SHIP_WIDTH, SHIP_HEIGHT });
	down.PushBack({ 94, 153, SHIP_WIDTH, SHIP_HEIGHT });
	down.loop = false;
	down.speed = 0.1f;

	downback.PushBack({ 94, 131, SHIP_WIDTH, SHIP_HEIGHT });
	downback.PushBack({ 94, 108, SHIP_WIDTH, SHIP_HEIGHT });
	downback.loop = false;
	downback.speed = 0.1f;

	// Turbo

	turbo_idle.PushBack({ 73, 116, 12, 5 });
	turbo_idle.PushBack({ 61, 116, 12, 5 });
	turbo_idle.PushBack({ 42, 116, 12, 5 });
	turbo_idle.loop = true;
	turbo_idle.speed = 0.8f;*/



}

j1Player::~j1Player()
{}

// Load assets
bool j1Player::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->tex->Load("assets/Archer/Archer2.png"); 
	/*
	laser_sound = App->audio->LoadSoundEffect("Music/Sounds_effects/Laser_Shot_Type-3_(Main_Ships).wav");
	basic_attack_sound = App->audio->LoadSoundEffect("Music/Sounds_effects/Laser_Shot_Type-1_(Main_Ships).wav");
	helix_sound = App->audio->LoadSoundEffect("Music/Sounds_effects/Laser_Shot_Type-4_(Main_Ships).wav");

	c_player = App->collision->AddCollider({ position.x, position.y, 27, 17 }, COLLIDER_PLAYER, this);

	player_death = App->audio->LoadSoundEffect("Music/Sounds_effects/Player_Death_Explosion.wav");
	change_weapon_sound = App->audio->LoadSoundEffect("Music/Sounds_effects/Laser_Shot_Type_CHANGE.wav");

	life = 3;*/
	return ret;
}

// Unload assets
bool j1Player::CleanUp()
{


	LOG("Unloading player");
	/*App->audio->UnloadSoundEffect(player_death);
	App->audio->UnloadSoundEffect(laser_sound);
	App->audio->UnloadSoundEffect(basic_attack_sound);
	App->audio->UnloadSoundEffect(change_weapon_sound);
	App->audio->UnloadSoundEffect(helix_sound);

	App->textures->Unload(graphics);

	current_animation = &idle;*/

	return true;
}

// Update: draw background
bool j1Player::Update(float dt)
{
	current_animation = &idle;
	float speed = 0.5;

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
	{
		position.x -= speed;
	}
	
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		position.x += speed;
	}
	
	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));
	/*
	if ((App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT || player_down == true) && position.y < App->render->camera.y / SCREEN_SIZE + SCREEN_HEIGHT - SHIP_HEIGHT)
	{
		location.y += speed;
		player_idle = true;
		reverse = false;
		if (current_animation != &down)
		{
			down.Reset();
			current_animation = &down;
		}

	}

	else if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_UP || (player_idle == true && player_down == false && reverse == false))
		if (current_animation != &downback)
		{
			downback.Reset();
			current_animation = &downback;
			player_idle = false;

		}

	if ((App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT || player_up == true) && position.y > App->render->camera.y / SCREEN_SIZE)
	{
		location.y -= speed;
		player_idle = true;
		reverse = true;
		if (current_animation != &up)
		{
			up.Reset();
			current_animation = &up;
			//anim_turbo = &turbo_up;

		}
	}

	else if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_UP || (player_idle == true && player_up == false && reverse == true))
		if (current_animation != &upback)
		{
			upback.Reset();
			current_animation = &upback;
			//anim_turbo = &turbo_up;
			player_idle = false;

		}
	

	//anim_turbo = &turbo_idle;

	

	if (destroyed == false) {
		if (SDL_GameControllerGetAxis(App->input->controller1, SDL_CONTROLLER_AXIS_LEFTY) > 5000 && player_down == false)
		{
			player_down = true;
		}
		if (SDL_GameControllerGetAxis(App->input->controller1, SDL_CONTROLLER_AXIS_LEFTY) > 5000 == false)
		{
			player_down = false;
		}

		if (SDL_GameControllerGetAxis(App->input->controller1, SDL_CONTROLLER_AXIS_LEFTY) < -5000 && player_up == false)
		{
			player_up = true;
		}
		if (SDL_GameControllerGetAxis(App->input->controller1, SDL_CONTROLLER_AXIS_LEFTY) < -5000 == false)
		{
			player_up = false;
		}

	
		


		// Player controls input

		//pressed 
		if (SDL_GameControllerGetButton(App->input->controller1, SDL_CONTROLLER_BUTTON_A) && a_pressed == false)
		{
			shoot = true;
			a_pressed = true;
		}
		
		if (SDL_GameControllerGetButton(App->input->controller1, SDL_CONTROLLER_BUTTON_B) && b_pressed == false)
		{
			change = true;
			b_pressed = true;
		}

		//not pressed

		if (SDL_GameControllerGetButton(App->input->controller1, SDL_CONTROLLER_BUTTON_A) == false)
		{
			a_pressed = false;
		}
		if (SDL_GameControllerGetButton(App->input->controller1, SDL_CONTROLLER_BUTTON_X) == false)
		{
			x_pressed = false;
		}
		if (SDL_GameControllerGetButton(App->input->controller1, SDL_CONTROLLER_BUTTON_B) == false)
		{
			b_pressed = false;
		}

		// Change player weapon

		if (App->input->keyboard[SDL_SCANCODE_C] == KEY_STATE::KEY_DOWN || change == true)
		{
			change = false;
			switch (change_weapon) {

			case CHANGE_WEAPON::BASIC_ATTACK:
				change_weapon = CHANGE_WEAPON::LASER;
				App->audio->PlaySoundEffect(change_weapon_sound);

				break;

			case CHANGE_WEAPON::LASER:
				change_weapon = CHANGE_WEAPON::BACK_SHOOT;
				App->audio->PlaySoundEffect(change_weapon_sound);

				break;

			case CHANGE_WEAPON::BACK_SHOOT:
				change_weapon = CHANGE_WEAPON::HELIX;
				App->audio->PlaySoundEffect(change_weapon_sound);

				break;

			case CHANGE_WEAPON::HELIX:
				change_weapon = CHANGE_WEAPON::BASIC_ATTACK;
				App->audio->PlaySoundEffect(change_weapon_sound);

				break;
			}
		}


		// POWERUP
		if (App->input->keyboard[SDL_SCANCODE_X] == KEY_STATE::KEY_DOWN || powerup == true)
		{
			powerup = false;
			switch (power_up) {

			case POWER_UPS::POWER_UP_BASIC:
				power_up = POWER_UPS::POWER_UP_1;
				App->UI->n_powerup = 2;
				break;

			case POWER_UPS::POWER_UP_1:
				power_up = POWER_UPS::POWER_UP_2;
				App->UI->n_powerup = 3;
				break;

			case POWER_UPS::POWER_UP_2:
				power_up = POWER_UPS::POWER_UP_3;
				App->UI->n_powerup = 4;
				break;

			case POWER_UPS::POWER_UP_3:
				power_up = POWER_UPS::POWER_UP_4;
				App->UI->n_powerup = 5;
				break;

			case POWER_UPS::POWER_UP_4:
				power_up = POWER_UPS::POWER_UP_5;
				App->UI->n_powerup = 6;
				break;

			case POWER_UPS::POWER_UP_5:
				power_up = POWER_UPS::POWER_UP_6;
				App->UI->n_powerup = 7;
				break;

				
			}
		}
		//cunado muere el jugador el power up se desincrementa
		if (powerup_desincrement == true)
		{
			powerup_desincrement = false;
			switch (power_up) {


			case POWER_UPS::POWER_UP_1:
				power_up = POWER_UPS::POWER_UP_BASIC;
				App->UI->n_powerup = 1;
				break;

			case POWER_UPS::POWER_UP_2:
				power_up = POWER_UPS::POWER_UP_1;
				App->UI->n_powerup = 2;
				break;

			case POWER_UPS::POWER_UP_3:
				power_up = POWER_UPS::POWER_UP_2;
				App->UI->n_powerup = 3;
				break;

			case POWER_UPS::POWER_UP_4:
				power_up = POWER_UPS::POWER_UP_3;
				App->UI->n_powerup = 4;
				break;

			case POWER_UPS::POWER_UP_5:
				power_up = POWER_UPS::POWER_UP_4;
				App->UI->n_powerup = 5;
				break;

			case POWER_UPS::POWER_UP_6:
				power_up = POWER_UPS::POWER_UP_5;
				App->UI->n_powerup = 6;
				break;
			}
		}
		//
		//////////

		// Shoot 
		if (Reset_time_bullets) {
			Bullet_time_init = SDL_GetTicks();
			Reset_time_bullets = false;
		}
		Bullet_delay = SDL_GetTicks() - Bullet_time_init;

		if ((App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || shoot == true) && Bullet_delay >= 100)
		{
			Bullet_delay = 0;
			Reset_time_bullets = true;
			shoot = false;
			switch (power_up) {
			case POWER_UPS::POWER_UP_BASIC:
				switch (change_weapon) {

				case CHANGE_WEAPON::BASIC_ATTACK:
					App->particles->AddParticle(App->particles->basic_shoot_0_down, position.x + 15, position.y + 11, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->basic_shoot_0_up, position.x + 15, position.y + 7, COLLIDER_PLAYER_SHOT);
					App->audio->PlaySoundEffect(basic_attack_sound);
					//App->UI->score += 100;
					break;

				case CHANGE_WEAPON::LASER:
					App->particles->AddParticle(App->particles->laser_0, position.x + 20, position.y + 10, COLLIDER_PLAYER_SHOT);
					App->audio->PlaySoundEffect(laser_sound);
					break;

				case CHANGE_WEAPON::BACK_SHOOT:
					App->particles->AddParticle(App->particles->back_shoot_0, position.x + 20, position.y + 10, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->back_shoot_0_back, position.x + 15, position.y + 10, COLLIDER_PLAYER_SHOT);
					App->audio->PlaySoundEffect(laser_sound);
					break;

				case CHANGE_WEAPON::HELIX:
					App->particles->AddParticle(App->particles->helix_01_1, position.x + 20, position.y + 11, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->helix_01_2, position.x + 20, position.y + 7, COLLIDER_PLAYER_SHOT);
					App->audio->PlaySoundEffect(helix_sound);
					break;
				}

				break;

			case POWER_UPS::POWER_UP_1:
				switch (change_weapon) {

				case CHANGE_WEAPON::BASIC_ATTACK:
					App->particles->AddParticle(App->particles->basic_shoot_1_down, position.x + 20, position.y + 12, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->basic_shoot_1_up, position.x + 20, position.y + 4, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->basic_shoot_1, position.x + 26, position.y + 10, COLLIDER_PLAYER_SHOT);
					App->audio->PlaySoundEffect(basic_attack_sound);
					break;

				case CHANGE_WEAPON::LASER:
					App->particles->AddParticle(App->particles->laser_1, position.x + 12, position.y - 2, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_1_5, position.x + 12, position.y + 7, COLLIDER_PLAYER_SHOT);
					App->audio->PlaySoundEffect(laser_sound);
					break;

				case CHANGE_WEAPON::BACK_SHOOT:
					App->particles->AddParticle(App->particles->back_shoot_0, position.x + 20, position.y + 10, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->back_shoot_0_back, position.x + 15, position.y + 7, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->back_shoot_0_back, position.x + 15, position.y + 13, COLLIDER_PLAYER_SHOT);
					App->audio->PlaySoundEffect(laser_sound);
					break;

				case CHANGE_WEAPON::HELIX:
					App->particles->AddParticle(App->particles->helix_01_1, position.x + 13, position.y + 11, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->helix_01_2, position.x + 13, position.y + 7, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->helix_01_3, position.x + 26, position.y + 9, COLLIDER_PLAYER_SHOT);
					App->audio->PlaySoundEffect(helix_sound);
					break;
				}




				break;

			case POWER_UPS::POWER_UP_2:
				switch (change_weapon) {

				case CHANGE_WEAPON::BASIC_ATTACK:
					App->particles->AddParticle(App->particles->basic_shoot_2_down, position.x + 20, position.y + 12, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->basic_shoot_2_up, position.x + 20, position.y + 0, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->basic_shoot_2, position.x + 22, position.y + 9, COLLIDER_PLAYER_SHOT);
					App->audio->PlaySoundEffect(basic_attack_sound);
					break;

				case CHANGE_WEAPON::LASER:
					App->particles->AddParticle(App->particles->laser_1, position.x + 12, position.y - 2, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_1_5, position.x + 12, position.y + 7, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_2, position.x + 5, position.y - 2, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_2_5, position.x + 5, position.y + 7, COLLIDER_PLAYER_SHOT);
					App->audio->PlaySoundEffect(laser_sound);
					break;

				case CHANGE_WEAPON::BACK_SHOOT:
					App->particles->AddParticle(App->particles->back_shoot_0, position.x + 20, position.y + 7, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->back_shoot_0, position.x + 20, position.y + 13, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->back_shoot_2_diagonal_up, position.x + 10, position.y + 7, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->back_shoot_2_diagonal_down, position.x + 10, position.y + 8, COLLIDER_PLAYER_SHOT);
					App->audio->PlaySoundEffect(laser_sound);
					break;

				case CHANGE_WEAPON::HELIX:
					App->particles->AddParticle(App->particles->helix_02_1, position.x + 13, position.y + 11, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->helix_02_2, position.x + 13, position.y + 7, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->helix_02_3, position.x + 26, position.y + 9, COLLIDER_PLAYER_SHOT);
					App->audio->PlaySoundEffect(helix_sound);
					break;
				}

				break;
			case POWER_UPS::POWER_UP_3:
				switch (change_weapon) {

				case CHANGE_WEAPON::BASIC_ATTACK:
					App->particles->AddParticle(App->particles->basic_shoot_3_down, position.x + 20, position.y + 12, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->basic_shoot_3_up, position.x + 20, position.y - 2, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->basic_shoot_2, position.x + 24, position.y + 9, COLLIDER_PLAYER_SHOT);
					App->audio->PlaySoundEffect(basic_attack_sound);
					break;

				case CHANGE_WEAPON::LASER:
					App->particles->AddParticle(App->particles->laser_3_up, position.x + 12, position.y - 2, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_3_down, position.x + 12, position.y + 7, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_3_up_back, position.x + 5, position.y - 2, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_3_down_back, position.x + 5, position.y + 7, COLLIDER_PLAYER_SHOT);
					App->audio->PlaySoundEffect(laser_sound);
					break;

				case CHANGE_WEAPON::BACK_SHOOT:
					App->particles->AddParticle(App->particles->back_shoot_0, position.x + 20, position.y + 7, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->back_shoot_0, position.x + 20, position.y + 13, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->back_shoot_2_diagonal_up, position.x + 10, position.y + 7, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->back_shoot_2_diagonal_down, position.x + 10, position.y + 8, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->back_shoot_3_back, position.x, position.y + 8, COLLIDER_PLAYER_SHOT);
					App->audio->PlaySoundEffect(laser_sound);
					break;

				case CHANGE_WEAPON::HELIX:
					App->particles->AddParticle(App->particles->helix_03_1, position.x + 10, position.y + 13, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->helix_03_2, position.x + 10, position.y + 5, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->helix_02_1, position.x + 23, position.y + 13, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->helix_02_2, position.x + 23, position.y + 5, COLLIDER_PLAYER_SHOT);
					App->audio->PlaySoundEffect(helix_sound);
					break;
				}
				break;

			case POWER_UPS::POWER_UP_4:
				switch (change_weapon) {

				case CHANGE_WEAPON::BASIC_ATTACK:
					App->particles->AddParticle(App->particles->basic_shoot_3_down, position.x + 20, position.y + 12, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->basic_shoot_3_up, position.x + 20, position.y - 3, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->basic_shoot_4_down, position.x + 20, position.y + 12, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->basic_shoot_4_up, position.x + 20, position.y + 4, COLLIDER_PLAYER_SHOT);
					App->audio->PlaySoundEffect(basic_attack_sound);
					break;

				case CHANGE_WEAPON::LASER:
					App->particles->AddParticle(App->particles->laser_4_up, position.x + 5, position.y - 10, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_4_down, position.x + 5, position.y + 4, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_4_up_back, position.x - 10, position.y - 10, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_4_down_back, position.x - 10, position.y + 4, COLLIDER_PLAYER_SHOT);
					App->audio->PlaySoundEffect(laser_sound);
					break;

				case CHANGE_WEAPON::BACK_SHOOT:
					App->particles->AddParticle(App->particles->back_shoot_0, position.x + 20, position.y + 7, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->back_shoot_0, position.x + 20, position.y + 13, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->back_shoot_3_diagonal_up, position.x + 10, position.y + 7, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->back_shoot_3_diagonal_down, position.x + 10, position.y + 8, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->back_shoot_3_back, position.x, position.y + 8, COLLIDER_PLAYER_SHOT);
					App->audio->PlaySoundEffect(laser_sound);
					break;

				case CHANGE_WEAPON::HELIX:
					App->particles->AddParticle(App->particles->helix_04_1, position.x + 23, position.y + 13, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->helix_04_2, position.x + 23, position.y + 5, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->helix_03_1, position.x + 10, position.y + 13, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->helix_03_2, position.x + 10, position.y + 5, COLLIDER_PLAYER_SHOT);
					App->audio->PlaySoundEffect(helix_sound);
					break;
				}
				break;

			case POWER_UPS::POWER_UP_5:
				switch (change_weapon) {

				case CHANGE_WEAPON::BASIC_ATTACK:
					App->particles->AddParticle(App->particles->basic_shoot_3_down, position.x + 20, position.y + 12, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->basic_shoot_3_up, position.x + 20, position.y - 5, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->basic_shoot_5_down, position.x + 20, position.y + 10, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->basic_shoot_5_up, position.x + 20, position.y, COLLIDER_PLAYER_SHOT);
					App->audio->PlaySoundEffect(basic_attack_sound);
					break;

				case CHANGE_WEAPON::LASER:
					App->particles->AddParticle(App->particles->laser_5_up, position.x + 5, position.y - 10, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_5_down, position.x + 5, position.y + 4, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_5_up_back, position.x - 10, position.y - 10, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_5_down_back, position.x - 10, position.y + 4, COLLIDER_PLAYER_SHOT);
					App->audio->PlaySoundEffect(laser_sound);
					break;

				case CHANGE_WEAPON::BACK_SHOOT:
					App->particles->AddParticle(App->particles->back_shoot_0_5, position.x + 17, position.y + 11, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->back_shoot_0_up, position.x + 14, position.y + 1, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->back_shoot_0_down, position.x + 14, position.y + 12, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->back_shoot_3_diagonal_up, position.x + 10, position.y + 7, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->back_shoot_3_diagonal_down, position.x + 10, position.y + 8, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->back_shoot_3_back, position.x, position.y + 8, COLLIDER_PLAYER_SHOT);
					App->audio->PlaySoundEffect(laser_sound);
					break;


				case CHANGE_WEAPON::HELIX:
					App->particles->AddParticle(App->particles->helix_05_3, position.x + 26, position.y + 9, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->helix_05_1, position.x + 23, position.y + 13, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->helix_05_2, position.x + 23, position.y + 5, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->helix_03_1, position.x + 10, position.y + 13, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->helix_03_2, position.x + 10, position.y + 5, COLLIDER_PLAYER_SHOT);
					App->audio->PlaySoundEffect(helix_sound);
					break;
				}
				break;

			case POWER_UPS::POWER_UP_6:
				switch (change_weapon) {

				case CHANGE_WEAPON::BASIC_ATTACK:
					App->particles->AddParticle(App->particles->basic_shoot_6_down, position.x + 20, position.y + 12, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->basic_shoot_6_up, position.x + 20, position.y - 11, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->basic_shoot_5_down, position.x + 20, position.y + 12, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->basic_shoot_5_up, position.x + 20, position.y - 1, COLLIDER_PLAYER_SHOT);
					App->audio->PlaySoundEffect(basic_attack_sound);
					break;

				case CHANGE_WEAPON::LASER:
					App->particles->AddParticle(App->particles->laser_6_up, position.x + 5, position.y - 30, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_6_down, position.x + 5, position.y, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_6_up_back, position.x - 25, position.y - 30, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_6_down_back, position.x - 25, position.y, COLLIDER_PLAYER_SHOT);
					App->audio->PlaySoundEffect(laser_sound);
					break;

				case CHANGE_WEAPON::BACK_SHOOT:
					App->particles->AddParticle(App->particles->back_shoot_1_5, position.x + 20, position.y + 9, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->back_shoot_0_up, position.x + 14, position.y + 1, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->back_shoot_0_down, position.x + 14, position.y + 12, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->back_shoot_3_diagonal_up, position.x + 10, position.y + 7, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->back_shoot_3_diagonal_down, position.x + 10, position.y + 8, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->back_shoot_3_back, position.x, position.y + 8, COLLIDER_PLAYER_SHOT);
					App->audio->PlaySoundEffect(laser_sound);
					break;

				case CHANGE_WEAPON::HELIX:
					App->particles->AddParticle(App->particles->helix_05_3, position.x + 26, position.y + 9, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->helix_05_1, position.x + 23, position.y + 13, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->helix_05_2, position.x + 23, position.y + 5, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->helix_06_1, position.x + 10, position.y + 13, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->helix_06_2, position.x + 10, position.y + 5, COLLIDER_PLAYER_SHOT);
					App->audio->PlaySoundEffect(helix_sound);
					break;

				}
			}
		}
	}
	*/
	//GOD MODE
/*
	if (App->input->keyboard[SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN) {
		if (god_mode)
			god_mode = false;
		else god_mode = true;
	}

	if (!god_mode)
	{
		if (App->player2->IsEnabled() == true)
			App->player2->c_player2->SetPos(App->player2->position.x, App->player2->position.y);

		c_player->SetPos(position.x, position.y);
	}
	else
	{
		c_player->SetPos(-100, -100);
		if (App->player2->IsEnabled() == true)
			App->player2->c_player2->SetPos(-100, -100);
	}


	if (time_finished == false)
	{
		time_final = SDL_GetTicks() - time_init;
		if (time_final <= 2000 && time_final >= 1000) {
			location.x += 1;
			position.x = App->render->camera.x / SCREEN_SIZE + location.x;
			position.y = App->render->camera.y / SCREEN_SIZE + location.y;

		}

		else {
			position.x = App->render->camera.x / SCREEN_SIZE + location.x;
			position.y = App->render->camera.y / SCREEN_SIZE + location.y;


		}

		if (time_final > 2000) destroyed = false;
		if (time_final >= 4000)
		{
			time_finished = true;
			god_mode = false;

		}

		// Draw everything -------------------------------------- parpadeo
		if (time_final % 100 <= 50) {
			App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));
			App->render->Blit(graphics, position.x - 12, position.y + 8, &(anim_turbo->GetCurrentFrame()));
		}
	}


	else {


		// Draw everything --------------------------------------
		App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));
		App->render->Blit(graphics, position.x - 12, position.y + 8, &(anim_turbo->GetCurrentFrame()));

		position.x = App->render->camera.x / SCREEN_SIZE + location.x;
		position.y = App->render->camera.y / SCREEN_SIZE + location.y;

	}




	if ((App->input->keyboard[SDL_SCANCODE_BACKSPACE] == KEY_DOWN || SDL_GameControllerGetButton(App->input->controller2, SDL_CONTROLLER_BUTTON_A)) && App->fade->IsFading() == false && App->players_menu->cr > 0)
	{
		App->player2->Enable();
		App->players_menu->cr--;
	}
	*/


	return true;
}

void j1Player::OnCollision(Collider* c1, Collider* c2)
{
	/*if (c_player != nullptr && c_player == c1 && App->fade->IsFading() == false && c2 != App->power_up->c_power_up)
	{
		//code
		if (!god_mode) {
			App->audio->PlaySoundEffect(player_death);
			App->particles->AddParticle(App->particles->explosion, position.x, position.y);
			life--;
			destroyed = true;
			powerup_desincrement = true;
			PlayerSpawn();
			if (life <= 0) {
				App->UI->time_dead = 0;
				App->UI->Cuenta_atras_number = 9;
				App->UI->time_dead_init = SDL_GetTicks();

				//App->player->Disable();
				//App->fade->FadeToBlack(App->level01, App->game_over, 1);
			}
		}
	}
	if (c_player != nullptr && c_player == c1 && App->fade->IsFading() == false && c2 == App->power_up->c_power_up)
	{
		App->power_up->Disable();
	}*/
}
