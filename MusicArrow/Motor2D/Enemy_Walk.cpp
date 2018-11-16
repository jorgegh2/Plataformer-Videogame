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
#include "j1Textures.h"
#include "Animation.h"

Enemy_Walk::Enemy_Walk(int x, int y) : Entity(x, y)
{

	//EXAMPLE
	walkLeft = App->tex->CreateAnimation("zombie", "walkLeft", true);
	walkRight = App->tex->CreateAnimation("zombie", "walkRight", true);
	deadLeft = App->tex->CreateAnimation("zombie", "deadLeft", false);
	deadRight = App->tex->CreateAnimation("zombie", "deadRight", false);
	zombiesound = App->audio->LoadFx("audio/zombie.wav");

	originalpos.x = position.x = x;
	originalpos.y = position.y = y;


	collider = App->collision->AddCollider({ (int)position.x, (int)position.y, 86, 119 }, COLLIDER_WALKENEMY, App->entities);
	timer.Start();
}

void Enemy_Walk::Move(float dt)
{
	NormalizeAnimations(dt);

	speed.x = 30 * dt;

	if (isDead == false)
		isDead = App->collision->CollisionToWorld(collider, movement);

	if (movement[down] == true)
		CalculateGravity(dt);


	iPoint enemy_tiles_pos = App->map->WorldToMap(position.x, position.y);
	iPoint player_tiles_pos = App->map->WorldToMap(App->entities->player->position.x, App->entities->player->position.y);


	if (player_tiles_pos.x - enemy_tiles_pos.x <= 3 && player_tiles_pos.x - enemy_tiles_pos.x >= -3)
	{
		App->pathfinding->CreatePathManhattan(enemy_tiles_pos, player_tiles_pos, enemy_path);

	}
	else {

		if (timer.Read() > 2000) {

			if (movingLeft) {
				movingLeft = false;
				timer.Start();
				animation = &walkLeft;
			}
			else {
				movingLeft = true;
				timer.Start();
				animation = &walkRight;
			}
		}

		if (movingLeft)
			App->pathfinding->CreatePathManhattan(enemy_tiles_pos, { enemy_tiles_pos.x + 1 , enemy_tiles_pos.y }, enemy_path);
		else
			App->pathfinding->CreatePathManhattan(enemy_tiles_pos, { enemy_tiles_pos.x - 1 , enemy_tiles_pos.y }, enemy_path);


	}

	if (i < enemy_path.Count()) {
		iPoint tileInMap = App->map->MapToWorld(enemy_path[i].x, enemy_path[i].y);

		if (isDead == true)
		{
			Dead();

		}
		else if (enemy_tiles_pos.x <= enemy_path[i].x && position.x < tileInMap.x && movement[right] == true) {
			position.x += speed.x;
			animation = &walkRight;
			current_in_path = true;
		}
		else if (enemy_tiles_pos.x >= enemy_path[i].x && position.x > tileInMap.x && movement[left] == true) {
			position.x -= speed.x;
			animation = &walkLeft;
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


	walkLeft.speed = App->tex->NormalizeAnimSpeed("zombie", "walkLeft", dt);
	walkRight.speed = App->tex->NormalizeAnimSpeed("zombie", "walkRight", dt);
	deadLeft.speed = App->tex->NormalizeAnimSpeed("zombie", "deadLeft", dt);
	deadRight.speed = App->tex->NormalizeAnimSpeed("zombie", "deadRight", dt);

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
			animation = &deadLeft;
		}
		else
			animation = &deadRight;

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