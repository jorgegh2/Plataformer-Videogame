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
	
	idle = App->tex->CreateAnimation("frog", "idle", true);
	walk = App->tex->CreateAnimation("frog", "walk", true);
	jump = App->tex->CreateAnimation("frog", "jump", true);
	
	zombiesound = App->audio->LoadFx("audio/fx/zombie.wav");

	originalpos.x = position.x = x;
	originalpos.y = position.y = y;


	collider = App->collision->AddCollider(colliderRect, COLLIDER_ENEMY, App->entities);
	timer.Reset();
}

bool Enemy_Walk::Awake(pugi::xml_node& config)
{
	return true;
}

void Enemy_Walk::Move(float dt)
{
	BROFILER_CATEGORY("Enemy_WalkPath", Profiler::Color::Gray);
	animation = &idle;
	NormalizeAnimations(dt);


	speed.x = 30 * dt;
	speed.y = 30 * dt;

	if (isDead == false)
		isDead = App->collision->CollisionToWorld(collider, movement);

	if (movement[down] == true)
		CalculateGravity(dt);

	if (position.DistanceManhattan(App->entities->player->position) < 1500)
		Agro = true;
	else
		Agro = false;


	iPoint enemy_tiles_pos = App->map->WorldToMap(position.x, position.y);
	iPoint player_tiles_pos = App->map->WorldToMap(App->entities->player->position.x, App->entities->player->position.y);


	if (Agro && timer.ReadSec() >= 0.1)
	{
		//App->pathfinding->CreatePathManhattan(enemy_tiles_pos, player_tiles_pos, enemy_path);

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

		//if (movingLeft)
			//App->pathfinding->CreatePathManhattan(enemy_tiles_pos, { enemy_tiles_pos.x + 1 , enemy_tiles_pos.y }, enemy_path);
		//else
			//App->pathfinding->CreatePathManhattan(enemy_tiles_pos, { enemy_tiles_pos.x - 1 , enemy_tiles_pos.y }, enemy_path);


	}

	if (i < enemy_path.Count()) {
		iPoint tileInMap = App->map->MapToWorld(enemy_path[i].x, enemy_path[i].y);

		if (isDead == true)
		{
			Dead();

		}
		else if (enemy_tiles_pos.x <= enemy_path[i].x && position.x < tileInMap.x && movement[right] == true) {
			position.x += speed.x;
			animation = &walk;
			current_in_path = true;
		}
		else if (enemy_tiles_pos.x >= enemy_path[i].x && position.x > tileInMap.x && movement[left] == true) {
			position.x -= speed.x;
			animation = &walk;
			current_in_path = true;
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
	//Trap for colliders work "good" speed.y = speed.y + g; //* timer.ReadSec();

		

	//if (speed.y >= 0)
	//{
	//	if (speed.y < AllDistances.distancePositiveY.Modulo)
	//		position.y += speed.y;
	//	else
	//	{
	//		position.y += AllDistances.distancePositiveY.Modulo;
	//		jstate = ONFLOOR;

	
	
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

void Enemy_Walk::NormalizeAnimations(float dt) 
{
	BROFILER_CATEGORY("NormalizeAnimationsEnemy", Profiler::Color::Gray);

	idle.speed = App->tex->NormalizeAnimSpeed("frog", "idle", dt);
	walk.speed = App->tex->NormalizeAnimSpeed("frog", "walk", dt);
	jump.speed = App->tex->NormalizeAnimSpeed("frog", "jump", dt);
	

}

void Enemy_Walk::Dead()
{
	BROFILER_CATEGORY("DeadEnemy", Profiler::Color::Gray);
	if (now == 0) {
		now = SDL_GetTicks();
		App->audio->PlayFx(zombiesound, 1);
	}
	if (now + 1000 > SDL_GetTicks()) {
		if (movingLeft)
		{
			//animation = &dead;
		}
		else
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