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
#include "Enemy_Walk.h"
#include "j1Entity.h"
#include "j1Entities.h"
#include "Brofiler/Brofiler.h"

Enemy_Walk::Enemy_Walk(int x, int y, SDL_Rect colliderRect) : Entity(x, y)
{
	
	idle = App->tex->CreateAnimation("slime", "idle", true);
	walk = App->tex->CreateAnimation("slime", "walk", true);
	jump = App->tex->CreateAnimation("slime", "jump", true);
	
	zombiesound = App->audio->LoadFx("audio/fx/zombie.wav");

	originalpos.x = position.x = x;
	originalpos.y = position.y = y;


	collider = App->collision->AddCollider(colliderRect, COLLIDER_ENEMY, App->entities);
	timer.Reset();
}

void Enemy_Walk::Move(float dt)
{
	BROFILER_CATEGORY("Enemy_WalkPath", Profiler::Color::Gray);
	animation = &idle;
	NormalizeAnimations(dt);


	speed.x = 30 * dt;
	speed.y = 30 * dt;

	if (movement[down] == true)
		CalculateGravity(dt);

	if (position.DistanceManhattan(App->entities->player->position) < 1500)
		Agro = true;
	else
		Agro = false;


	iPoint enemy_tiles_pos = App->map->WorldToMap(position.x, position.y);
	iPoint player_tiles_pos = App->map->WorldToMap(App->entities->player->position.x, App->entities->player->position.y);

	//hit enemies or get a hit
	/*if (App->entities->player->AllDistances.distancePositiveX.nearestColliderType == COLLIDER_ENEMY && App->entities->player->AllDistances.distancePositiveX.Modulo <= 0)
	{

		if (App->entities->player->IsAttacking == true)
		{
			isDead = true;
		}
		else
		{
			App->entities->player->player_lifes -= 1;
			App->entities->player->IsHurting = true;
			App->entities->player->hurting = position.x;
			App->entities->player->jstate = HIT;
			

		}

	}*/

	if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
		ShowPath = !ShowPath;

	if (ShowPath)
		DrawPath();


	if (Agro && timer.ReadSec() >= 0.1)
	{
		App->pathfinding->CreatePathManhattan(enemy_tiles_pos, player_tiles_pos, enemy_path);

	}
	else {

		if (timer.Read() > 2000) {

			if (movingLeft) {
				movingLeft = false;
				timer.Reset();
				animation = &walk;
			}
			else {
				movingLeft = true;
				timer.Reset();
				animation = &walk;
			}
		}

	}

	if (i < enemy_path.Count()) {
		iPoint tileInMap = App->map->MapToWorld(enemy_path[i].x, enemy_path[i].y);

		if (isDead == true)
		{
			Dead();

		}
		else if (enemy_tiles_pos.x < enemy_path[i].x && position.x < tileInMap.x && movement[right] == true) {
			position.x += speed.x*2;
			current_in_path = true;
			animation = &jump;
		}
		else if (enemy_tiles_pos.x > enemy_path[i].x && position.x > tileInMap.x && movement[left] == true) {
			position.x -= speed.x*2;
			current_in_path = true;
			animation = &jump;
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


void Enemy_Walk::CalculateGravity(float dt) 
{
	BROFILER_CATEGORY("CalculateGravityEnemy", Profiler::Color::Gray);
		
		if (speed_jump < 20)
		{
			speed_jump += gravity;
		}
		else
		{
			speed_jump = 20;
		}

		if(speed_jump < AllDistances.distancePositiveY.Modulo)
			position.y += speed_jump;
		else
			position.y += AllDistances.distancePositiveY.Modulo;

				if (movement[down] == false && speed_jump > 0)
				{
					speed_jump = 0;
				}
			
}

void Enemy_Walk::DrawPath()
{
	for (int i = 0; i < enemy_path.Count(); i++)
	{
		iPoint p = App->map->MapToWorld(enemy_path[i].x, enemy_path[i].y);

		SDL_Rect quad = { p.x, p.y, App->map->data.tile_width, App->map->data.tile_height };
		App->render->DrawQuad(quad, 255, 0, 255, 255);
	}
}

void Enemy_Walk::NormalizeAnimations(float dt) 
{
	BROFILER_CATEGORY("NormalizeAnimationsEnemy", Profiler::Color::Gray);

	idle.speed = App->tex->NormalizeAnimSpeed("frog", "idle", dt);
	walk.speed = App->tex->NormalizeAnimSpeed("frog", "walk", dt);
	jump.speed = App->tex->NormalizeAnimSpeed("frog", "jump", dt);
	

}



bool Enemy_Walk::Save(pugi::xml_node& data) const
{
	BROFILER_CATEGORY("SaveEnemy", Profiler::Color::Gray);
	pugi::xml_node enemy_walk_node = data.append_child("enemywalk");

	pugi::xml_node pos_node = enemy_walk_node.append_child("position");

	pos_node.append_attribute("x") = position.x;
	pos_node.append_attribute("y") = position.y;

	pugi::xml_node speed_node = enemy_walk_node.append_child("speed");

	speed_node.append_attribute("x") = speed.x;
	speed_node.append_attribute("y") = speed.y;

	pugi::xml_node speed_jump_node = enemy_walk_node.append_child("speedjump");

	speed_jump_node.append_attribute("speedjump") = speed_jump;

	pugi::xml_node gravity_node = enemy_walk_node.append_child("gravity");

	gravity_node.append_attribute("gravity") = gravity;

	pugi::xml_node dead_node = enemy_walk_node.append_child("isDead");

	dead_node.append_attribute("isDead") = isDead;

	pugi::xml_node path_node = enemy_walk_node.append_child("path");

	path_node.append_attribute("currentpath") = current_in_path;

	pugi::xml_node now_node = enemy_walk_node.append_child("now");

	now_node.append_attribute("now") = now;

	pugi::xml_node movingLeft_node = enemy_walk_node.append_child("movingleft");

	movingLeft_node.append_attribute("movingleft") = movingLeft;

	return true;
}

bool Enemy_Walk::Load(pugi::xml_node& data)
{
	BROFILER_CATEGORY("LoadEnemy", Profiler::Color::Gray);
	//load player position
	position.x = data.child("enemywalk").child("position").attribute("x").as_int();
	position.y = data.child("enemywalk").child("position").attribute("y").as_int();

	//load speed position
	speed.x = data.child("enemywalk").child("speed").attribute("x").as_int();
	speed.y = data.child("enemywalk").child("speed").attribute("y").as_int();

	//load speed jump
	speed_jump = data.child("enemywalk").child("speedjump").attribute("speedjump").as_int();

	//load gravity
	speed_jump = data.child("enemywalk").child("gravity").attribute("gravity").as_int();

	//load dead state
	isDead = data.child("enemywalk").child("isDead").attribute("isDead").as_bool();

	//load current path
	current_in_path = data.child("enemywalk").child("path").attribute("currentpath").as_bool();

	//load now
	now = data.child("enemywalk").child("now").attribute("now").as_int();

	//load moving left
	movingLeft = data.child("enemywalk").child("movingleft").attribute("movingleft").as_bool();

	return true;
}