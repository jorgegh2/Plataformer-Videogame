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
	animation = &idle;
	NormalizeAnimations(dt);


	speed.x = 30 * dt;
	speed.y = 30 * dt;

	if (isDead == false)
		isDead = App->collision->CollisionToWorld(collider, movement);

	if (movement[down] == true)
		CalculateGravity(dt);


	iPoint enemy_tiles_pos = App->map->WorldToMap(position.x, position.y);
	iPoint player_tiles_pos = App->map->WorldToMap(App->entities->player->position.x, App->entities->player->position.y);


	if (player_tiles_pos.x - enemy_tiles_pos.x <= 3 && player_tiles_pos.x - enemy_tiles_pos.x >= -3)
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


void Enemy_Walk::CalculateGravity(float dt) {
	//Trap for colliders work "good" 
	if (speed_jump < 20)
	{
		speed_jump += gravity;
	}
	else
	{
		speed_jump = 20;
	}

	position.y += speed_jump;

	if (movement[down] == false && speed_jump > 0)
	{
		speed_jump = 0;
	}
}

void Enemy_Walk::NormalizeAnimations(float dt) {


	idle.speed = App->tex->NormalizeAnimSpeed("frog", "idle", dt);
	walk.speed = App->tex->NormalizeAnimSpeed("frog", "walk", dt);
	jump.speed = App->tex->NormalizeAnimSpeed("frog", "jump", dt);
	

}

void Enemy_Walk::Dead()
{

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