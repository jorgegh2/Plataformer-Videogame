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

	// fALLING

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
	die.loop = true;
	die.speed = 0.15f;

	//-------------------------------------


}

j1Player::~j1Player()
{}

// Load assets
bool j1Player::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->tex->Load("assets/Archer/Archer2.png");

	//If the module input has been disabled in the DEAD state
	if(!App->input->IsEnabled()) App->input->Enable();

	p2List_item<MapObjects*>* item_object = nullptr;
	
	for (item_object = App->map->data.objects.start; item_object; item_object = item_object->next)
	{
		if (item_object->data->StartPoint.x != 0 && item_object->data->StartPoint.y != 0)
		{
			StartPoint.x = item_object->data->StartPoint.x;
			StartPoint.y = item_object->data->StartPoint.y;

		}
	}

	position.x = StartPoint.x;
	position.y = StartPoint.y;

	App->render->camera.x = -position.x * App->win->GetScale() + WIDTH_CANVAS;
	App->render->camera.y = -position.y * App->win->GetScale() + HEIGHT_CANVAS;

	speed = { 8,0 };
	myGravity = 1;
	dashCount = 0;
	current_animation = &idle;

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
	step = "audio/fx/steps.wav";
	audio_step = App->audio->LoadFx(step);
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
	LOG("Unloading audio");
	App->audio->CleanUp();

	return true;
}

// Update: draw background
bool j1Player::Update(float dt)
{
	velocityX = 0;
	//Distance d = App->collision->FinalDistance;
	Distance d_positiveY = App->collision->dPositiveY;
	Distance d_negativeX = App->collision->dNegativeX;
	Distance d_positiveX = App->collision->dPositiveX;
	Distance d_negativeY = App->collision->dNegativeY;
	current_animation = &idle;


	//Horizontal movement
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && !locked_to_left)
	{
		if (d_negativeX.Modulo < speed.x && d_negativeX.nearestColliderType != COLLIDER_PLATAFORM)
			position.x -= d_negativeX.Modulo;
					
		else position.x -= speed.x;

		velocityX = -speed.x;
		current_animation = &walk;
		App->audio->PlayFx(audio_step);

	}
	else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && !locked_to_right)
	{
		if (d_positiveX.Modulo < speed.x && d_positiveX.nearestColliderType != COLLIDER_PLATAFORM)
			position.x += d_positiveX.Modulo;

		else position.x += speed.x;

		velocityX = speed.x;
		current_animation = &walk;
		App->audio->PlayFx(audio_step);

	}

	if (App->input->GetKey(SDL_SCANCODE_J) == KEY_DOWN && dashCount < 1 && jstate == ONAIR && App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		if(dashCount == 0) App->time->Reset();
		dashCount = 1;
		current_animation = &hit;
		App->audio->PlayFx(audio_dash);

		if (velocityX < 0) 
		{
			position.x -= speed.x * App->time->DeltaTime();
		
		}
		jstate = LANDING;
		
	}
	else if(App->input->GetKey(SDL_SCANCODE_J) == KEY_DOWN && dashCount < 1 && jstate == ONAIR && App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		App->time->Reset();
		dashCount = 1;
		current_animation = &hit;
		App->audio->PlayFx(audio_dash);
		if (velocityX > 0) 
		{
			position.x += speed.x * App->time->DeltaTime();
			
		}
		else jstate = LANDING;
		
	}

	//Flip player sprite if x speed is negative
	if (velocityX < 0)flip = SDL_FLIP_HORIZONTAL;
	if (velocityX > 0)flip = SDL_FLIP_NONE;

	//Jump
	switch (jstate)
	{

	case JUMP:
		if (dashCount == 0)
		{
		App->time->Reset();
		speed.y = -15;
		jstate = ONAIR;
		}
		
		break;

	case ONFLOOR:

		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		{
			jstate = JUMP;
			current_animation = &jump;
			current_animation->Reset();
			App->audio->PlayFx(audio_jumping);
		}
		else if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
			jstate = JUMP;
			current_animation = &jump;
			current_animation->Reset();
			App->audio->PlayFx(audio_jumping);
		}
		else if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
			jstate = JUMP;
			current_animation = &jump;
			current_animation->Reset();
			App->audio->PlayFx(audio_jumping);
		}
		jumpCount = 0;
		dashCount = 0;
		App->time->Reset();

		break;

	case ONAIR:

			speed.y = speed.y + myGravity * App->time->DeltaTime();
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
					App->audio->PlayFx(audio_bump);
				}
				else
				{
					position.y += speed.y;
				}
			}
			if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && jumpCount < 1)
			{

				jstate = JUMP;
				App->time->Reset();
				speed.y = -15;
				jstate = ONAIR;
				current_animation = &jump;
				current_animation->Reset();
				App->audio->PlayFx(audio_jumping);
				jumpCount = 1;
				
			}

			//DEAD condition
			if (d_positiveY.Modulo == 0 && d_positiveY.nearestColliderType == COLLIDER_WATER)
			{
				jstate = DEAD;
				App->input->Disable();
			}

		current_animation = &jump;
		
		break;

	case LANDING:

		current_animation = &fall;

		break;

	case DEAD:

		current_animation = &die;
		App->audio->PlayFx(audio_dead);
		c_player->SetPos(-1000, -1000);
		App->time->Reset();
		speed.y = -2;
		speed.y = speed.y + myGravity * App->time->DeltaTime();
		position.y += speed.y * App->time->DeltaTime();

		if (position.y > App->render->camera.y) //ADD FADE TO BLACK

			App->audio->PlayFx(audio_finishdead);

			break;
	}
	if (d_positiveY.Modulo != 0.0f) jstate = ONAIR;

	c_player->SetPos(position.x, position.y);
	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()), flip);
	SDL_Rect offSet{ (-App->render->camera.x / App->win->GetScale()) + 200, (-App->render->camera.y / App->win->GetScale()) + 600, 800, 600 };
	App->render->DrawQuad(offSet, 255, 255, 255, 80);

	if (position.x + c_player->rect.w > offSet.w + offSet.x)
	{
		App->render->camera.x = -(position.x * App->win->GetScale() - 423);
	}
	else if (position.x < offSet.x)
	{
		App->render->camera.x = -(position.x * App->win->GetScale() - 100);
	}


	if (position.y < offSet.y)
	{
		App->render->camera.y = -(position.y * App->win->GetScale() - 300);
	}
	else if (position.y + c_player->rect.h > offSet.y + offSet.h)
	{
		App->render->camera.y = -(position.y * App->win->GetScale() - 515);
	}

	

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

void j1Player::OnCollision(Collider* c1, Collider* c2){}

