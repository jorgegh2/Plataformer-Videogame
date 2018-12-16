#include "j1App.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Player.h"
#include "j1Collision.h"
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
	OriginPos = { collider->rect.x, collider->rect.y };
	

	//------ New Animations ------

	// IDLE1

	idle.PushBack({ 46, 68, 77, 110 });
	idle.PushBack({ 136, 72, 94, 108 });
	idle.PushBack({ 242, 72, 94, 111 });
	idle.PushBack({ 350, 68, 88, 110 });
	idle.PushBack({ 447, 71, 94, 107 });
	idle.loop = true;
	idle.speed = 0.2f;

	// IDLE2

	idle2.PushBack({ 46, 221, 77, 110 });
	idle2.PushBack({ 142, 218, 94, 108 });
	idle2.PushBack({ 247, 214, 94, 111 });
	idle2.PushBack({ 349, 215, 89, 111 });
	idle2.PushBack({ 461, 215, 94, 108 });
	idle2.loop = true;
	idle2.speed = 0.2f;


	// RUN

	run.PushBack({ 46, 371, 105, 110 });
	run.PushBack({ 180, 372, 77, 113 });
	run.PushBack({ 292, 367, 99, 116 });
	run.PushBack({ 411, 375, 100, 107 });
	run.PushBack({ 534, 368, 71, 111 });
	run.PushBack({ 630, 371, 99, 108 });
	run.PushBack({ 741, 364, 127, 108 });
	run.PushBack({ 889, 367, 127, 108 });
	run.loop = true;
	run.speed = 0.4f;


	// JUMP

	jump.PushBack({ 22, 508, 105, 127 });
	jump.PushBack({ 144, 514, 97, 128 });
	jump.PushBack({ 356, 525, 85, 94 });
	jump.PushBack({ 463, 526, 86, 83 });
	jump.PushBack({ 566, 550, 86, 63 });
	jump.PushBack({ 692, 549, 85, 71 });
	jump.PushBack({ 811, 545, 86, 74 });
	jump.PushBack({ 932, 557, 88, 63 });
	jump.PushBack({ 1049, 549, 91, 79 });
	jump.PushBack({ 1171, 545, 85, 94 });
	jump.PushBack({ 1277, 536, 113, 117 });
	jump.loop = false;
	jump.speed = 0.3f;

	// SLIDE 1

	slide1.PushBack({ 46, 665, 108, 116 });
	slide1.PushBack({ 174, 660, 116, 118 });
	slide1.PushBack({ 313, 665, 117, 124 });
	slide1.PushBack({ 453, 676, 116, 94 });
	slide1.loop = false;
	slide1.speed = 0.05f;

	// SLIDE 2

	slide2.PushBack({ 46, 829, 116, 94 });
	slide2.PushBack({ 175, 829, 94, 93 });
	slide2.PushBack({ 289, 823, 83, 105 });
	slide2.PushBack({ 395, 830, 94, 93 });
	slide2.PushBack({ 509, 834, 116, 94 });
	slide2.loop = true;
	slide2.speed = 0.05f;

	// SLIDE 3

	slide3.PushBack({ 50, 960, 108, 91 });
	slide3.PushBack({ 188, 959, 97, 91 });
	slide3.loop = false;
	slide3.speed = 0.05f;

	// ATTACK

	attack.PushBack({ 50, 1098, 147, 94 });
	attack.PushBack({ 203, 1104, 141, 94 });
	attack.PushBack({ 359, 1112, 136, 94 });
	attack.PushBack({ 512, 1118, 130, 94 });
	attack.loop = true;
	attack.speed = 0.02f;

	//CHARGE FIREBALL

	charge.PushBack({ 434, 1252, 102, 91 });
	charge.PushBack({ 342, 1250, 77, 82 });
	charge.loop = true;
	charge.speed = 0.1f;

	// FIREBALL

	fireball.PushBack({ 566, 1273, 161, 60 });
	fireball.PushBack({ 739, 1278, 150, 61 });
	fireball.PushBack({ 898, 1281, 149, 61 });
	fireball.loop = true;
	fireball.speed = 0.05f;

	//OUT FIREBALL

	outfire.PushBack({ 1091, 1266, 85, 94 });
	outfire.PushBack({ 1197, 1257, 113, 117 });
	outfire.loop = false;
	outfire.speed = 0.05f;


	// HIT

	hit.PushBack({ 45, 1398, 117, 128 });
	hit.PushBack({ 208, 1399, 116, 136 });
	hit.loop = true;
	hit.speed = 0.2f;


	// DIE

	die.PushBack({ 370, 1401, 136, 127 });
	die.PushBack({ 521, 1401, 116, 113 });
	die.PushBack({ 652, 1378, 132, 117 });
	die.PushBack({ 808, 1434, 160, 66 });
	die.PushBack({ 986, 1420, 160, 72 });
	die.loop = false;
	die.speed = 0.15f;


	// TO GIANT

	giant1.PushBack({ 1180, 1773, 100, 109 });
	giant1.PushBack({ 1289, 1779, 83, 100 });
	giant1.PushBack({ 1389, 1758, 99, 120 });
	giant1.PushBack({ 1505, 1717, 133, 161 });
	giant1.PushBack({ 1655, 1655, 184, 223 });
	giant1.loop = false;
	giant1.speed = 0.15f;

	// TO NORMAL

	giant3.PushBack({ 1655, 1655, 184, 223 });
	giant3.PushBack({ 1505, 1717, 133, 161 });
	giant3.PushBack({ 1389, 1758, 99, 120 });
	giant3.PushBack({ 1289, 1779, 83, 100 });
	giant3.PushBack({ 1180, 1773, 100, 109 });
	giant3.loop = false;
	giant3.speed = 0.15f;

	// GIANT

	giant2.PushBack({ 49, 1550, 193, 316 });
	giant2.PushBack({ 281, 1550, 207, 309 });
	giant2.PushBack({ 527, 1556, 229, 310 });
	giant2.PushBack({ 781, 1550, 213, 316 });
	giant2.PushBack({ 63, 1920, 192, 317 });
	giant2.PushBack({ 296, 1913, 207, 324 });
	giant2.PushBack({ 556, 1913, 247, 330 });
	giant2.PushBack({ 849, 1920, 213, 309 });
	giant2.loop = false;
	giant2.speed = 0.15f;


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
	graphics = App->tex->Load("assets/Star/star.png");
	
	//Set Lifes
	player_lifes = 5;
	//Set Charging Bar
	chargingBar = 0;
	hurting = 0;

	ResetPlayer();

	//Load background music
	const char* path = "audio/music/musicstage1.wav";

	//Play background music
	App->audio->PlayMusic(path);

	

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

	float g = gravity * dt;
	float speedDtX = speed.x * dt;
	velocityX = speedDtX;
	
	//Horizontal movement

	if(IsCharging != true && IsHurting != true){

		current_animation = &run;
	
		if (AllDistances.distancePositiveX.Modulo < speedDtX && AllDistances.distancePositiveX.nearestColliderType != COLLIDER_PLATAFORM)
		{
			position.x += AllDistances.distancePositiveX.Modulo;
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
		else position.x += speedDtX;

	}

	////Flip player sprite if x speed is negative
	//if (velocityX < 0)flip = SDL_FLIP_HORIZONTAL;
	//if (velocityX > 0)flip = SDL_FLIP_NONE;

	//hit enemies or get a hit
		if (AllDistances.distancePositiveX.nearestColliderType == COLLIDER_ENEMY && AllDistances.distancePositiveX.Modulo == 0)
		{

			if (IsAttacking) 
			{
				//enemies dead animation and destroy
			} 
			else 
			{
				player_lifes -= 1;
				IsHurting = true;
				current_animation = &hit;
				hurting = position.x;
				jstate = HIT;
				App->audio->PlayFx(audio_jumping, 1);
			
			}
			
		}
		if (AllDistances.distancePositiveX.nearestColliderType == COLLIDER_FLOOR && AllDistances.distancePositiveX.Modulo == 0)
		{
			player_lifes -= 1;
			IsHurting = true;
			current_animation = &hit;
			hurting = position.x;
			jstate = HIT;
			App->audio->PlayFx(audio_jumping, 1);

		}
		if (player_lifes <= 0) jstate = DEAD;

	//PLAYER STATES
	switch (jstate)
	{

	case JUMP:
		timer.Reset();
		speed.y = -1500*dt;
		jstate = ONAIR;
				
		break;

	case SJUMP:
		timer.Reset();
		speed.y = -1500 * dt/2;
		jstate = ONAIR;

		break;

	case ONFLOOR:
		

			if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
			{
				jstate = JUMP;
				current_animation = &jump;
				current_animation->Reset();
				App->audio->PlayFx(audio_jumping, 1);
			}
			if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
			{
				
				IsCharging = true;
				chargingBar += 20;
				current_animation = &charge;
				
				App->audio->PlayFx(audio_jumping, 1);
				if (chargingBar >= 100)
				{
					App->audio->PlayFx(audio_jumping, 1); // ring charge is completed

				}
				
				
			}
			else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
			{

				current_animation = &charge;

			}
			if (App->input->GetKey(SDL_SCANCODE_A) == KEY_UP)
			{

				if (chargingBar >= 100)
				{
					chargingBar = 100;
					jstate = FIREBALL;

				}
				else
				{
					jstate = ONFLOOR;
				}

			}
			
			if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
			{
				current_animation = &attack;
				current_animation->Reset();
				IsAttacking = true;
				App->audio->PlayFx(audio_jumping, 1);
			}
			if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
			{
				
				current_animation = &slide1;
				current_animation->Reset();
				App->audio->PlayFx(audio_jumping, 1);
			}

			if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
			{
				
				current_animation = &slide2;
				current_animation->Reset();
				App->audio->PlayFx(audio_jumping, 1);
			}

			if (App->input->GetKey(SDL_SCANCODE_S) == KEY_UP)
			{
				
				current_animation = &slide3;
				current_animation->Reset();
				App->audio->PlayFx(audio_jumping, 1);
			}
			
			if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
			{
				jstate = SJUMP;
				current_animation = &slide2;
				current_animation->Reset();
				App->audio->PlayFx(audio_jumping, 1);
			}




			
			timer.Reset();
		
		break;

	case ONAIR:
			
		

			speed.y = speed.y + g;
		

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

			//DEAD condition
			if (AllDistances.distancePositiveY.Modulo == 0 && AllDistances.distancePositiveY.nearestColliderType == COLLIDER_WATER)
			{
				jstate = DEAD;
				timer.Reset();
				App->audio->PlayFx(audio_dead, 1);
				App->input->Disable();
			}
			else if (player_lifes == 0)
			{
				jstate = DEAD;
				timer.Reset();
				App->audio->PlayFx(audio_dead, 1);
				App->input->Disable();
			}

			current_animation = &jump;
		
		break;

	case HIT:

		current_animation = &hit;
		
		position.x -= speedDtX * 2;

		if (hurting - position.x > 300)
		{
			jstate = ONFLOOR;
			IsHurting = false;

		}

		break;

	case FIREBALL:

		current_animation = &fireball;
		IsAttacking = true;
		position.x += speedDtX *2;
		chargingBar -= 5;

		if (chargingBar <= 0)
		{
			chargingBar = 0;
			jstate = ONAIR;
			IsCharging = false;
			IsAttacking = false;

		}

		break;

	case DEAD:

		current_animation = &die;
		
		collider->SetPos(-1000, -1000);

		speed.y = -1;
		speed.y = speed.y + gravity * timer.ReadSec();
		position.y += speed.y * timer.ReadSec();

		if (position.y > (-App->render->camera.y + App->render->camera.h)*2)
		{
			App->audio->PlayFx(audio_finishdead, 1);
			ResetPlayer();
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
	if (jstate!= GODMODE)
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
		player_state = SJUMP;
		break;

	case 2:
		player_state = ONFLOOR;
		break;

	case 3:
		player_state = ONAIR;
		break;

	case 4:
		player_state = HIT;
		break;

	case 5:
		player_state = FIREBALL;
		break;

	case 6:
		player_state = DEAD;
		break;

	case 7:
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
