#include "p2Defs.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Collision.h"
#include "j1Player.h"
#include "j1Audio.h"
#include "j1Module.h"
#include "p2Log.h"
#include "Animation.h"
#include "j1Map.h"
#include "j1Pathfinding.h"
#include "p2DynArray.h"
#include "Enemy_fly.h"
#include "j1Entity.h"
#include "j1Entities.h"

Enemy_Fly::Enemy_Fly(int x, int y, SDL_Rect colliderRect) : Entity(x, y)
{

	fly = App->tex->CreateAnimation("crow", "fly", true);
	attack = App->tex->CreateAnimation("crow", "attack", true);

	flysound = App->audio->LoadFx("audio/fx/glide.wav");
	animation = &fly;

	originalpos.x = position.x = x;
	originalpos.y = position.y = y;


	collider = App->collision->AddCollider(colliderRect, COLLIDER_ENEMY, App->entities);
}





void Enemy_Fly::Move(float dt)
{
	speed.x = 200 * dt;
	speed.y = 200 * dt;
	animation = &fly;
	NormalizeAnimations(dt);

	if (soundtimer.Read() > 2000) {
		App->audio->PlayFx(flysound, 1);
		soundtimer.Reset();
	}



	if (position.DistanceManhattan(App->entities->player->position) < 1500)
		Agro = true;
	else
		Agro = false;
	   
	iPoint enemy_tiles_pos = App->map->WorldToMap(position.x, position.y);
	iPoint player_tiles_pos = App->map->WorldToMap(App->entities->player->position.x, App->entities->player->position.y);

	if (Agro && timer.ReadSec() >= 0.1)
	{
		timer.Reset();
		App->pathfinding->CreatePathManhattan(enemy_tiles_pos, player_tiles_pos, enemy_path);
		originalpos = App->map->MapToWorld(enemy_tiles_pos.x, enemy_tiles_pos.y);
	}
	

	if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
		ShowPath = !ShowPath;

	if(ShowPath)
		DrawPath();


	if (i < enemy_path.Count()) {
		//enemy_path[i] != nullptr;
		//No faltaba comprobar que enemy_path era null eso ya lo hace el count, el player entraba en la siguiente tile y ya te detectaba la comparacion pero se quedaba tocando
		// el iPoint tileInMap coje la posicion en el mapa de la tile para dirigir al enemigo hasta los puntos de la esquina opuesta asi hace el path bien y se queda dentro de la tile
		iPoint tileInMap = App->map->MapToWorld(enemy_path[i].x, enemy_path[i].y);
		if (isDead == true)
		{
			Dead();
		}

		else if (enemy_tiles_pos.y < enemy_path[i].y && position.y < tileInMap.y && movement[down] == true) {
			position.y += speed.y;
			current_in_path = true;
			animation = &attack;
		}
		else if (enemy_tiles_pos.y > enemy_path[i].y && position.y > tileInMap.y && movement[up] == true) {
			position.y -= speed.y;
			current_in_path = true;
			animation = &attack;
		}
		else if (enemy_tiles_pos.x < enemy_path[i].x && position.x < tileInMap.x && movement[right] == true) {
			position.x += speed.x;
			current_in_path = true;
			animation = &attack;
		}
		else if (enemy_tiles_pos.x > enemy_path[i].x && position.x > tileInMap.x && movement[left] == true) {
			position.x -= speed.x;
			current_in_path = true;
			animation = &attack;
		}
		else {
			current_in_path = false;
		}

		if (current_in_path == false)
			i++;


	
	}
	else {
		i = 0;
		enemy_path.Clear();
	}

	

}

void Enemy_Fly::DrawPath()
{
	for (int i = 0; i < enemy_path.Count(); i++)
	{
		iPoint p = App->map->MapToWorld(enemy_path[i].x, enemy_path[i].y);

		SDL_Rect quad = { p.x, p.y, App->map->data.tile_width, App->map->data.tile_height };
		App->render->DrawQuad(quad, 255, 255, 0, 255);
	}
}


void Enemy_Fly::NormalizeAnimations(float dt) {

	fly.speed = App->tex->NormalizeAnimSpeed("crow", "fly", dt);
	attack.speed = App->tex->NormalizeAnimSpeed("crow", "attack", dt);

}



bool Enemy_Fly::Save(pugi::xml_node& data) const
{
	pugi::xml_node enemy_fly_node = data.append_child("enemyfly");

	pugi::xml_node pos_node = enemy_fly_node.append_child("position");

	pos_node.append_attribute("x") = position.x;
	pos_node.append_attribute("y") = position.y;

	pugi::xml_node speed_node = enemy_fly_node.append_child("speed");

	speed_node.append_attribute("x") = speed.x;
	speed_node.append_attribute("y") = speed.y;

	pugi::xml_node dead_node = enemy_fly_node.append_child("isDead");

	dead_node.append_attribute("isDead") = isDead;

	pugi::xml_node path_node = enemy_fly_node.append_child("path");

	path_node.append_attribute("currentpath") = current_in_path;

	pugi::xml_node now_node = enemy_fly_node.append_child("now");

	now_node.append_attribute("now") = now;

	pugi::xml_node movingLeft_node = enemy_fly_node.append_child("movingleft");

	movingLeft_node.append_attribute("movingleft") = movingLeft;

	return true;
}

bool Enemy_Fly::Load(pugi::xml_node& data)
{
	//load player position
	position.x = data.child("enemyfly").child("position").attribute("x").as_int();
	position.y = data.child("enemyfly").child("position").attribute("y").as_int();

	//load speed position
	speed.x = data.child("enemyfly").child("speed").attribute("x").as_int();
	speed.y = data.child("enemyfly").child("speed").attribute("y").as_int();

	//load dead state
	isDead = data.child("enemyfly").child("isDead").attribute("isDead").as_bool();

	//load current path
	current_in_path = data.child("enemyfly").child("path").attribute("currentpath").as_bool();

	//load now
	now = data.child("enemyfly").child("now").attribute("now").as_int();

	//load moving left
	movingLeft = data.child("enemyfly").child("movingleft").attribute("movingleft").as_bool();

	return true;
}