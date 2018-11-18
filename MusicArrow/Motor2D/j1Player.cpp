//#include "Globals.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Input.h"
//#include "ModulePlayersMenu.h"
//#include "ModuleRender.h"
#include "j1Player.h"
//#include "SDL\include\SDL.h"
//#include "ModuleParticles.h"
#include "j1Collision.h"
//#include "ModuleFadeToBlack.h"
//#include "Level01.h"
//#include "ModuleGameOver.h"
//#include "ModuleGameIntroduction.h"
//#include "ModuleAudio.h"
//#include "ModuleFonts.h"
//#include "UI.h"
//#include "ModulePowerUp.h"
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



j1Player::j1Player() : Entity()
{


}

j1Player::j1Player(int x, int y, SDL_Rect colliderRect) : Entity(x, y)
{
	graphics = NULL;
	current_animation = NULL;
	c_player = App->collision->AddCollider(colliderRect, COLLIDER_PLAYER, nullptr); //cambiar c_player to collider (heredada de entity)
	OriginPos = {c_player->rect.x, c_player->rect.y };
	//name.create("player");

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
	idle.speed = 0.3f;

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
	alert.speed = 0.05f;

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
	walk.speed = 0.5f;


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
	run.speed = 0.05f;


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
	jump.speed = 0.1f;

	// FALLING

	fall.PushBack({ 1251, 1296, 165, 156 });
	fall.PushBack({ 1444, 1305, 160, 160 });
	fall.loop = false;
	fall.speed = 0.05f;

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
	shot.speed = 0.05f;



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
	hit.speed = 0.05f;


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
	die.loop = false;
	die.speed = 0.15f;

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
	return ret;
}
j1Player::~j1Player()
{}

// Load assets
bool j1Player::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->tex->Load("assets/Archer/Archer2.png");
	
	godmodeCount = 0;

	ResetPlayer();

	//Load background music
	const char* path = "audio/music/musicstage1.wav";

	//Play background music
	App->audio->PlayMusic(path);

	//Load FX
	jumping = "audio/fx/jump.wav";
	audio_jumping = App->audio->LoadFx(jumping);
	dash = "audio/fx/dash.wav";
	audio_dash = App->audio->LoadFx(dash);
	bump = "audio/fx/bump.wav";
	audio_bump = App->audio->LoadFx(bump);
	dead = "audio/fx/dead.wav";
	audio_dead = App->audio->LoadFx(dead);
	finishdead = "audio/fx/finishdead.wav";
	audio_finishdead = App->audio->LoadFx(finishdead);
	stageclear = "audio/fx/stageclear.wav";
	audio_stageclear = App->audio->LoadFx(stageclear);

	return ret;
}

// Unload assets
bool j1Player::CleanUp()
{


	LOG("Unloading player");
	App->tex->UnLoad(graphics);

	return true;
}

// Update: draw background
bool j1Player::Update(float dt)
{
	float g = gravity * dt;
	float speedDtX = speed.x * dt;
	velocityX = 0;
	//Distance d = App->collision->FinalDistance;
	Distance d_positiveY = App->collision->dPositiveY;
	Distance d_negativeX = App->collision->dNegativeX;
	Distance d_positiveX = App->collision->dPositiveX;
	Distance d_negativeY = App->collision->dNegativeY;
	current_animation = &idle;

	/*bool incamera = App->render->InCamera(c_player->rect);
	
	if (incamera)
	{
		LOG("yeeey");
	}*/

	//Horizontal movement

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && jstate != DEAD && jstate != GODMODE)
	{
		if (d_negativeX.Modulo < speedDtX && d_negativeX.nearestColliderType != COLLIDER_PLATAFORM)
			position.x -= d_negativeX.Modulo;

		else position.x -= speedDtX;

		velocityX = -speedDtX;
		current_animation = &walk;


	}
	else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && jstate != DEAD && jstate != GODMODE)
	{
		if (d_positiveX.Modulo < speedDtX && d_positiveX.nearestColliderType != COLLIDER_PLATAFORM)
		{
			position.x += d_positiveX.Modulo;
			if (d_positiveX.nearestColliderType == COLLIDER_FINISH_LEVEL)
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

		else 
			position.x += speedDtX;

		velocityX = speedDtX;
		current_animation = &walk;


	}

	//Dash movement
/*	if (App->input->GetKey(SDL_SCANCODE_J) == KEY_DOWN && dashCount < 1 && jstate == ONAIR && App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && jstate != DEAD && jstate != GODMODE)
	{
		if (dashCount == 0) App->time->Reset();
		dashCount = 1;
		current_animation = &hit;
		App->audio->PlayFx(audio_dash);

		if (velocityX < 0)
		{
			position.x -= speed.x * 4;

		}
		jstate = LANDING;

	}
	else if (App->input->GetKey(SDL_SCANCODE_J) == KEY_DOWN && dashCount < 1 && jstate == ONAIR && App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && jstate != DEAD && jstate != GODMODE)
	{
		App->time->Reset();
		dashCount = 1;
		current_animation = &hit;
		App->audio->PlayFx(audio_dash);
		if (velocityX > 0)
		{
			position.x += speed.x * 4;

		}
		else jstate = LANDING;

	}*/

	//Flip player sprite if x speed is negative
	if (velocityX < 0)flip = SDL_FLIP_HORIZONTAL;
	if (velocityX > 0)flip = SDL_FLIP_NONE;

	//PLAYER STATES
	switch (jstate)
	{

	case JUMP:
		if (dashCount == 0)
		{
		timer.Reset();
		speed.y = -938*dt;
		jstate = ONAIR;
		}
		
		break;

	case ONFLOOR:
		

			if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
			{
				jstate = JUMP;
				current_animation = &jump;
				current_animation->Reset();
				App->audio->PlayFx(audio_jumping, 1);
			}
			else if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
				jstate = JUMP;
				current_animation = &jump;
				current_animation->Reset();
				App->audio->PlayFx(audio_jumping, 1);
			}
			else if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
				jstate = JUMP;
				current_animation = &jump;
				current_animation->Reset();
				App->audio->PlayFx(audio_jumping, 1);
			}
			jumpCount = 0;
			dashCount = 0;
			timer.Reset();
		
		break;

	case ONAIR:
			
		

			speed.y = speed.y + g; //* timer.ReadSec();

		

			if (speed.y >= 0)
			{
				if (speed.y < d_positiveY.Modulo)
					position.y += speed.y;
				else
				{
					position.y += d_positiveY.Modulo;
					jstate = ONFLOOR;
				}
			}
			else
			{
				if (speed.y < -d_negativeY.Modulo && d_negativeY.nearestColliderType != COLLIDER_PLATAFORM)
				{
					position.y -= d_negativeY.Modulo;
					speed.y = 0;
					App->audio->PlayFx(audio_bump, 1);
				}
				else
				{
					position.y += speed.y;
				}
			}
			if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && jumpCount < 1)
			{

				jstate = JUMP;
				timer.Reset();
				speed.y = -15;
				jstate = ONAIR;
				current_animation = &jump;
				current_animation->Reset();
				App->audio->PlayFx(audio_jumping, 1);
				jumpCount = 1;

			}

			//DEAD condition
			if (d_positiveY.Modulo == 0 && d_positiveY.nearestColliderType == COLLIDER_WATER)
			{
				jstate = DEAD;
				timer.Reset();
				App->audio->PlayFx(audio_dead, 1);
				App->input->Disable();
			}

			current_animation = &jump;
		
		break;

	case LANDING:

		current_animation = &fall;

		break;

	case DEAD:

		current_animation = &die;
		
		c_player->SetPos(-1000, -1000);

		speed.y = -1;
		speed.y = speed.y + gravity * timer.ReadSec();
		position.y += speed.y * timer.ReadSec();

		if (position.y > (-App->render->camera.y + App->render->camera.h)*2) //ADD FADE TO BLACK
		{
			App->audio->PlayFx(audio_finishdead, 1);
			ResetPlayer();
		}
			break;

	case GODMODE:

		
			c_player->SetPos(-1000, -1000);
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

		if (d_positiveY.Modulo != 0.0f && jstate != DEAD) jstate = ONAIR;

		if (jstate != DEAD) c_player->SetPos(position.x, position.y);

		App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()), flip);
		SDL_Rect offSet{ (-App->render->camera.x / App->win->GetScale()) + 200, (-App->render->camera.y / App->win->GetScale()) + 600, 800, 600 };
		//13568 limite derecho del mapa
		//App->render->DrawQuad(offSet, 255, 255, 255, 80);
		
		int limit = -App->render->camera.x + App->render->camera.w;
		if (position.x + c_player->rect.w > offSet.w + offSet.x && limit < 13568)
		{
			App->render->camera.x = -(position.x * App->win->GetScale() - 423);
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
			else if (position.y + c_player->rect.h > offSet.y + offSet.h && -App->render->camera.y + App->render->camera.h < 1645)
			{
				App->render->camera.y = -(position.y * App->win->GetScale() - 515);
			}
		}

	

	}
	
	
	return true;
}

bool j1Player::Save(pugi::xml_node& data) const
{
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
		player_state = LANDING;
		break;

	case 4:
		player_state = DEAD;
		break;

	case 5:
		player_state = GODMODE;
		break;
	}
	return player_state;
}

void j1Player::ResetPlayer()
{
	//If the module input has been disabled in the DEAD state
	if (!App->input->IsEnabled()) App->input->Enable();

	p2List_item<MapObjects*>* item_object = nullptr;

	/*for (item_object = App->map->data.objects.start; item_object; item_object = item_object->next)
	{
		if (item_object->data->StartPoint.x != 0 && item_object->data->StartPoint.y != 0)
		{
			StartPoint.x = item_object->data->StartPoint.x;
			StartPoint.y = item_object->data->StartPoint.y;

		}
	}*/

	position.x = OriginPos.x;
	position.y = OriginPos.y;

	App->render->camera.x = -position.x * App->win->GetScale() + WIDTH_CANVAS;
	App->render->camera.y = -position.y * App->win->GetScale() + HEIGHT_CANVAS;

	dashCount = 0;
	jstate = ONAIR;
	current_animation = &idle;
}
