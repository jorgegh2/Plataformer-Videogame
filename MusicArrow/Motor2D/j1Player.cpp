#include "j1App.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Player.h"
#include "j1Collision.h"
#include "j1Entities.h"
#include "Time.h"
#include "p2Log.h"
#include "j1Map.h"
#include "j1Window.h"
#include "j1Render.h"
#include "j1Audio.h"
#include "j1Scene.h"
#include "j1FadeToBlack.h"
#include "j1Scene_Forest.h"
#include "j1Scene_Winter.h"
#include "Brofiler/Brofiler.h"



j1Player::j1Player() : Entity()
{


}

j1Player::j1Player(int x, int y, SDL_Rect colliderRect) : Entity(x, y)
{
	graphics = NULL;
	current_animation = NULL;
	collider = App->collision->AddCollider(colliderRect, COLLIDER_PLAYER, nullptr); 
	OriginPos = { x, y };
	

	//------ New Animations ------

	// IDLE

	idle.PushBack({ 27, 43, 134, 181 });
	idle.PushBack({ 575, 51, 126, 189 });
	idle.PushBack({ 739, 61, 131, 186 });
	idle.PushBack({ 929, 54, 132, 178 });
	idle.PushBack({ 1453, 59, 138, 188 });
	idle.PushBack({ 1636, 55, 134, 184 });
	idle.loop = true;
	idle.speed = 0.2f;

	
	// RUN

	run.PushBack({ 27, 43, 134, 181 });
	run.PushBack({ 191, 50, 147, 178 });
	run.PushBack({ 367, 62, 150, 173 });
	run.PushBack({ 575, 51, 126, 189 });
	run.PushBack({ 739, 61, 131, 186 });
	run.PushBack({ 929, 54, 132, 178 });
	run.PushBack({ 1089, 55, 151, 182 });
	run.PushBack({ 1262, 63, 156, 170 });
	run.PushBack({ 1453, 59, 138, 188 });
	run.PushBack({ 1636, 55, 134, 184 });
	run.loop = true;
	run.speed = 0.8f;


	// JUMP

	jump.PushBack({ 575, 51, 126, 189 });
	jump.PushBack({ 27, 43, 134, 181 });
	jump.PushBack({ 43, 302, 124, 120 });
	jump.PushBack({ 204, 308, 130, 126 });
	jump.PushBack({ 565, 304, 128, 129 });
	jump.PushBack({ 916, 313, 136, 129 });
	jump.PushBack({ 1105, 306, 126, 130 });
	jump.PushBack({ 1282, 302, 135, 137 });
	jump.PushBack({ 1262, 63, 156, 170 });
	jump.PushBack({ 1453, 59, 138, 188 });
	jump.PushBack({ 1636, 55, 134, 184 });
	jump.loop = false;
	jump.speed = 0.5f;

	// SLIDE

	slide1.PushBack({ 1468, 301, 172, 126 });
	slide1.loop = false;
	slide1.speed = 0.05f;

	// ATTACK

	attack.PushBack({ 50, 1098, 147, 94 });
	attack.PushBack({ 203, 1104, 141, 94 });
	attack.PushBack({ 359, 1112, 136, 94 });
	attack.PushBack({ 512, 1118, 130, 94 });
	attack.loop = true;
	attack.speed = 0.02f;


	// DIE

	die.PushBack({ 71, 1066, 97, 104 });
	die.PushBack({ 207, 1052, 122, 119 });
	die.loop = true;
	die.speed = 0.10f;


	//-------------------------------------


	position.x = x;
	position.y = y;
	
}

bool j1Player::Awake(pugi::xml_node& config)
{

	LOG("Loading Player Module");
	bool ret = true;
	
	speed = { config.child("player").child("vars").child("speed").attribute("speedX").as_float(), config.child("player").child("vars").child("speed").attribute("speedY").as_float() };
	gravity = config.child("player").child("vars").child("myGravity").attribute("value").as_float();

	//Load FX
	jumping = config.child("fxsound").child("jump").attribute("source").as_string();
	audio_jumping = App->audio->LoadFx(jumping);
	dash = config.child("fxsound").child("dash").attribute("source").as_string();
	audio_dash = App->audio->LoadFx(dash);
	bump = config.child("fxsound").child("bump").attribute("source").as_string();
	audio_bump = App->audio->LoadFx(bump);
	dead = config.child("fxsound").child("dead").attribute("source").as_string();
	audio_dead = App->audio->LoadFx(dead);
	finishdead = config.child("fxsound").child("finishdead").attribute("source").as_string();
	audio_finishdead = App->audio->LoadFx(finishdead);
	stageclear = config.child("fxsound").child("stageclear").attribute("source").as_string();
	audio_stageclear = App->audio->LoadFx(stageclear);


	return ret;
}
j1Player::~j1Player()
{}

// Load assets
bool j1Player::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->tex->Load("assets/Hero/hero_sprite.png");
	ResetPlayer();

	return ret;
}

// Unload assets
bool j1Player::CleanUp()
{
	BROFILER_CATEGORY("PlayerCleanUp", Profiler::Color::Beige);

	LOG("Unloading player");
	App->tex->UnLoad(graphics);

	return true;
}

// Update: draw background
bool j1Player::Update(float dt)
{
	BROFILER_CATEGORY("PlayerUpdate", Profiler::Color::Beige);
	if (App->isPaused)
	{
		App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()), flip);
		return true;
	}
		float g = gravity * dt * 1.5;
		float speedDtX = speed.x * dt * 2;
		velocityX = speedDtX;

		//Horizontal movement

		if (jstate != GODMODE) {

			current_animation = &idle;


			if (AllDistances.distancePositiveX.Modulo < speedDtX && AllDistances.distancePositiveX.nearestColliderType != COLLIDER_PLATAFORM)
			{
				position.x += AllDistances.distancePositiveX.Modulo;
				current_animation = &idle;
				if (AllDistances.distancePositiveX.nearestColliderType == COLLIDER_FINISH_LEVEL)
				{
					if (App->scene->current_scene == "scene_forest")
					{
						App->fadeToBlack->FadeToBlack(App->map_forest, App->map_winter);
					}
					else
					{
						App->fadeToBlack->FadeToBlack(App->map_winter, App->map_forest);
					}
				}
			}
			else if (IsRunning == true)
			{
				current_animation = &run;
				position.x += speedDtX;
			}

		}

		//Flip player sprite if x speed is negative
		if (velocityX < 0)flip = SDL_FLIP_HORIZONTAL;
		if (velocityX > 0)flip = SDL_FLIP_NONE;

		//DEAD CONDITIONS

		if (AllDistances.distancePositiveX.nearestColliderType == COLLIDER_ENEMY && AllDistances.distancePositiveX.Modulo == 0)
		{
			jstate = DEAD;
			timer.Reset();
			App->audio->PlayFx(audio_dead, 1);
			App->input->Disable();
		}
		if (AllDistances.distancePositiveY.nearestColliderType == COLLIDER_ENEMY && AllDistances.distancePositiveY.Modulo == 0)
		{
			jstate = DEAD;
			timer.Reset();
			App->audio->PlayFx(audio_dead, 1);
			App->input->Disable();
		}
		if (AllDistances.distanceNegativeY.nearestColliderType == COLLIDER_ENEMY && AllDistances.distanceNegativeY.Modulo == 0)
		{
			jstate = DEAD;
			timer.Reset();
			App->audio->PlayFx(audio_dead, 1);
			App->input->Disable();
		}
		if (AllDistances.distancePositiveX.nearestColliderType == COLLIDER_FLOOR && AllDistances.distancePositiveX.Modulo == 0)
		{
			jstate = DEAD;
			timer.Reset();
			App->audio->PlayFx(audio_dead, 1);
			App->input->Disable();
		}
		if (AllDistances.distancePositiveY.Modulo == 0 && AllDistances.distancePositiveY.nearestColliderType == COLLIDER_WATER)
		{
			jstate = DEAD;
			timer.Reset();
			App->audio->PlayFx(audio_dead, 1);
			App->input->Disable();
		}

		//SCORE CONDITIONS

		if (AllDistances.distancePositiveX.Modulo == 0 && AllDistances.distancePositiveX.nearestColliderType == COLLIDER_OBJECT)
		{
			App->entities->IsDead = true;
			score += 100;
			coins++;
			App->entities->DestroyEntities();
			App->audio->PlayFx(audio_dead, 1);
			
		}
		if (AllDistances.distancePositiveY.Modulo == 0 && AllDistances.distancePositiveY.nearestColliderType == COLLIDER_OBJECT)
		{
			App->entities->IsDead = true;
			score += 100;
			coins++;
			App->entities->DestroyEntities();
			App->audio->PlayFx(audio_dead, 1);

		}
		if (AllDistances.distanceNegativeY.Modulo == 0 && AllDistances.distanceNegativeY.nearestColliderType == COLLIDER_OBJECT)
		{
			App->entities->IsDead = true;
			score += 100;
			coins++;
			App->entities->DestroyEntities();
			App->audio->PlayFx(audio_dead, 1);

		}



	//PLAYER STATES
		switch (jstate)
		{

		case JUMP:
			timer.Reset();
			speed.y = -1500 * dt;
			jstate = ONAIR;

			break;

		case ONFLOOR:


			if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
			{
				jstate = JUMP;
				current_animation = &jump;
				current_animation->Reset();
				App->audio->PlayFx(audio_jumping, 1);
				IsRunning = true;
			}

			//if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
			//{
			//	
			//	IsCharging = true;
			//	chargingBar += 20;
			//	current_animation = &charge;
			//	
			//	App->audio->PlayFx(audio_jumping, 1);
			//	if (chargingBar >= 100)
			//	{
			//		App->audio->PlayFx(audio_jumping, 1); // ring charge is completed

			//	}
			//	
			//	
			//}
			//
			//if (App->input->GetKey(SDL_SCANCODE_A) == KEY_UP)
			//{

			//	if (chargingBar >= 100)
			//	{
			//		chargingBar = 100;
			//		jstate = FIREBALL;

			//	}
			//	else
			//	{
			//		jstate = ONFLOOR;
			//	}

			//}

			//Attack movement

			/*if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
			{
				current_animation = &attack;
				current_animation->Reset();
				IsAttacking = true;
				App->audio->PlayFx(audio_jumping, 1);
			}
			 else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_UP)
			{
				current_animation = &run;
				current_animation->Reset();
				IsAttacking = false;
				App->audio->PlayFx(audio_jumping, 1);
			}*/

			if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
			{

				collider->rect.w = 90;
				collider->rect.h = 126;

				current_animation = &slide1;
				current_animation->Reset();
				App->audio->PlayFx(audio_jumping, 1);


			}
			else if (App->input->GetKey(SDL_SCANCODE_S) == KEY_UP) {


				collider->rect.w = 130;
				collider->rect.h = 180;
				position.y -= 90;

			}


			timer.Reset();

			break;

		case ONAIR:

			speed.y = speed.y + (gravity *1.5*dt);


			if (speed.y >= 0)
			{
				if (speed.y < AllDistances.distancePositiveY.Modulo)
					position.y += speed.y;
				else
				{
					position.y += AllDistances.distancePositiveY.Modulo;
					jstate = ONFLOOR;
				}
			}
			else
			{
				if (speed.y < -AllDistances.distanceNegativeY.Modulo && AllDistances.distanceNegativeY.nearestColliderType != COLLIDER_PLATAFORM)
				{
					position.y -= AllDistances.distanceNegativeY.Modulo;
					speed.y = 0;
					App->audio->PlayFx(audio_bump, 1);
				}
				else
				{
					position.y += speed.y;
				}
			}

			current_animation = &jump;

			break;


		case DEAD:

			deadcont += 5;
			speed.x = 0;
			current_animation->Reset();
			current_animation = &die;
			collider->SetPos(-1000, -1000);
			App->audio->PlayFx(audio_finishdead, 1);
			

			if (deadcont >= 100) 
			{
				
				ResetPlayer();
				deadcont = 0;
				speed.x = 470;
				
			
			}
			else if (position.y > (-App->render->camera.y + App->render->camera.h) * 2)
			{
				
				ResetPlayer();
				deadcont = 0;
				speed.x = 470;
			}
			
			break;

		case GODMODE:


			collider->SetPos(-1000, -1000);
			App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()), flip);


			if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
			{
				position.x -= speedDtX;
				App->render->camera.x += speedDtX * App->win->GetScale();
			}
			if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
			{
				position.x += speedDtX;
				App->render->camera.x -= speedDtX * App->win->GetScale();
			}
			if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
			{
				position.y -= speedDtX;
				App->render->camera.y += speedDtX * App->win->GetScale();
			}
			if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
			{
				position.y += speedDtX;
				App->render->camera.y -= speedDtX * App->win->GetScale();
			}



			break;
		}

		//GOD MODE

		if (App->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN && !IsGodMode) {
			jstate = GODMODE;
			IsGodMode = true;
		}
		else if (App->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN && IsGodMode)
		{
			jstate = ONAIR;
			IsGodMode = false;
			timer.Reset();
		}


		//OffSet Camera
		if (jstate != GODMODE)
		{

			if (AllDistances.distancePositiveY.Modulo != 0.0f && jstate != DEAD) jstate = ONAIR;

			if (jstate != DEAD) collider->SetPos(position.x, position.y);

			App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()), flip);
			SDL_Rect offSet{ (-App->render->camera.x / App->win->GetScale()) + 200, (-App->render->camera.y / App->win->GetScale()) + 600, 800, 600 };

			int limit = -App->render->camera.x + App->render->camera.w;
			if (position.x + collider->rect.w > offSet.w + offSet.x && limit < 13568)
			{
				App->render->camera.x = -(position.x * App->win->GetScale() - 456);
			}
			else if (position.x < offSet.x && -App->render->camera.x > 1)
			{
				App->render->camera.x = -(position.x * App->win->GetScale() - 100);
			}

			if (jstate != DEAD) {
				if (position.y < offSet.y)
				{
					App->render->camera.y = -(position.y * App->win->GetScale() - 300);
				}
				else if (position.y + collider->rect.h > offSet.y + offSet.h && -App->render->camera.y + App->render->camera.h < 1645)
				{
					App->render->camera.y = -(position.y * App->win->GetScale() - 527);
				}
			}



		}
	
	return true;
}

bool j1Player::Save(pugi::xml_node& data) const
{
	BROFILER_CATEGORY("PlayerSave", Profiler::Color::Beige);
	pugi::xml_node player_node = data.append_child("player");
	pugi::xml_node pos_node = player_node.append_child("position");

	pos_node.append_attribute("x") = position.x;
	pos_node.append_attribute("y") = position.y;

	pugi::xml_node State_node = player_node.append_child("state");

	State_node.append_attribute("current_state") = jstate;

	pugi::xml_node speed_node = player_node.append_child("speed");

	speed_node.append_attribute("x") = speed.x;
	speed_node.append_attribute("y") = speed.y;

	return true;
}

bool j1Player::Load(pugi::xml_node& data)
{
	BROFILER_CATEGORY("PlayerLoad", Profiler::Color::Beige);
	//load player position
	position.x = data.child("player").child("position").attribute("x").as_int();
	position.y = data.child("player").child("position").attribute("y").as_int();

	//load speed position
	speed.x = data.child("player").child("speed").attribute("x").as_int();
	speed.y = data.child("player").child("speed").attribute("y").as_int();

	//load player state
	jstate = SetStateFromInt(data.child("player").child("state").attribute("current_state").as_int());

	return true;
}

state j1Player::SetStateFromInt(int state_as_int)
{
	state player_state;
	switch (state_as_int)
	{
	case 0:
		player_state = JUMP;
		break;

	case 1:
		player_state = ONFLOOR;
		break;

	case 2:
		player_state = ONAIR;
		break;

	case 3:
		player_state = DEAD;
		break;

	case 4:
		player_state = GODMODE;
		break;
	}
	return player_state;
}

void j1Player::ResetPlayer()
{
	BROFILER_CATEGORY("PlayerReset", Profiler::Color::Beige);
	//If the module input has been disabled in the DEAD state
	if (!App->input->IsEnabled()) App->input->Enable();

	position.x = OriginPos.x;
	position.y = OriginPos.y;

	App->render->camera.x = -position.x * App->win->GetScale() + WIDTH_CANVAS;
	App->render->camera.y = -position.y * App->win->GetScale() + HEIGHT_CANVAS;

	jstate = ONAIR;
	current_animation = &idle;
	
}
