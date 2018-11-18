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

	//App->entities posible error, original(App->entity)
	collider = App->collision->AddCollider(colliderRect, COLLIDER_ENEMY, App->entities);
}

bool Enemy_Fly::Awake(pugi::xml_node& config) 
{
	return true;
}



void Enemy_Fly::Move(float dt)
{
	if (isDead == false)
		isDead = App->collision->CollisionToWorld(collider, movement);
	speed.x = 90 * dt;
	speed.y = 90 * dt;
	animation = &fly;
	NormalizeAnimations(dt);

	if (soundtimer.Read() > 2000) {
		App->audio->PlayFx(flysound, 1);
		soundtimer.Reset();
	}


	iPoint enemy_tiles_pos = App->map->WorldToMap(position.x, position.y);
	iPoint player_tiles_pos = App->map->WorldToMap(App->entities->player->position.x, App->entities->player->position.y);

	if (player_tiles_pos.x - enemy_tiles_pos.x <= 5 && player_tiles_pos.x - enemy_tiles_pos.x >= -5 && player_tiles_pos.y - enemy_tiles_pos.y <= 5 && player_tiles_pos.y - enemy_tiles_pos.y >= -5)
	{
		App->pathfinding->CreatePathManhattan(enemy_tiles_pos, player_tiles_pos, enemy_path);
		originalpos = App->map->MapToWorld(enemy_tiles_pos.x, enemy_tiles_pos.y);
		DrawPath();
	}
	else {

		if (timer.Read() > 2000) {

			if (movingLeft) {
				movingLeft = false;
				timer.Reset();
				animation = &fly;
			}
			else 
			{
				movingLeft = true;
				timer.Reset();
				animation = &fly;
				App->audio->PlayFx(flysound, 1);
			}
			
		}
		if (movingLeft)
			App->pathfinding->CreatePathManhattan(enemy_tiles_pos, { enemy_tiles_pos.x + 1 , enemy_tiles_pos.y }, enemy_path);
		else
			App->pathfinding->CreatePathManhattan(enemy_tiles_pos, { enemy_tiles_pos.x - 1 , enemy_tiles_pos.y }, enemy_path);
	}


	//const p2DynArray<iPoint>* tmp_array = App->pathfinding->GetLastPath();
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

		else if (enemy_tiles_pos.y < enemy_path[i].y && position.y < tileInMap.y && movement[up] == true) {
			position.y += speed.y;
			current_in_path = true;
			animation = &attack;
			
		}
		else if (enemy_tiles_pos.y > enemy_path[i].y && position.y > tileInMap.y && movement[down] == true) {
			position.y -= speed.y;
			current_in_path = true;
			animation = &attack;
		}
		else if (enemy_tiles_pos.x <= enemy_path[i].x && position.x < tileInMap.x && movement[right] == true) {
			position.x += speed.x;
			current_in_path = true;
			animation = &attack;
		}
		else if (enemy_tiles_pos.x >= enemy_path[i].x && position.x > tileInMap.x && movement[left] == true) {
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
	}

}

void Enemy_Fly::DrawPath()
{
	for (int i = 0; i < enemy_path.Count(); i++)
	{
		iPoint p = { enemy_path.At(i)->x, enemy_path.At(i)->y };
		p.x -= App->map->data.tile_width / 2;
		p.y -= App->map->data.tile_height / 2;

		SDL_Rect quad = { p.x, p.y, App->map->data.tile_width, App->map->data.tile_height };
		App->render->DrawQuad(quad, 255, 255, 0, 75, true);
	}
}


void Enemy_Fly::NormalizeAnimations(float dt) {

	fly.speed = App->tex->NormalizeAnimSpeed("crow", "fly", dt);
	attack.speed = App->tex->NormalizeAnimSpeed("crow", "attack", dt);

}

void Enemy_Fly::Dead()
{

	if (now == 0) {
		now = SDL_GetTicks();

	}
	if (now + 1000 > SDL_GetTicks()) {
		
			//animation = &dead;
		

		// stop all movement, else player go out of map, bug
		movement[down] = false;
		movement[left] = false;
		movement[right] = false;
	}
	else
	{
		now = 0;
		death = true;
	}
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