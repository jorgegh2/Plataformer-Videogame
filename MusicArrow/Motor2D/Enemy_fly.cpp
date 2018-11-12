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
#include "j1Textures.h"


Enemy_Fly::Enemy_Fly(int x, int y) : Entity(x, y)
{

	// EXAMPLE

	walkLeft = App->tex->CreateAnimation("girl", "walkLeft", true);
	walkRight = App->tex->CreateAnimation("girl", "walkRight", true);
	deadRight = App->tex->CreateAnimation("girl", "deadRight", false);
	deadLeft = App->tex->CreateAnimation("girl", "deadLeft", false);
	flysound = App->audio->LoadFx("audio/glide.wav");
	animation = &walkLeft;

	originalpos.x = position.x = x;
	originalpos.y = position.y = y;

	collider = App->collision->AddCollider({ (int)position.x, (int)position.y,86,119 }, COLLIDER_ENEMY, App->entity);
}

void Enemy_Fly::Move(float dt)
{
	if (isDead == false)
		isDead = App->collision->CollisionToWorld(collider, movement);
	speed = 90 * dt;
	NormalizeAnimations(dt);

	if (soundtimer.Read() > 2000) {
		App->audio->PlayFx(flysound, 1);
		soundtimer.Start();
	}


	iPoint enemy_tiles_pos = App->map->WorldToMap(position.x, position.y);
	iPoint player_tiles_pos = App->map->WorldToMap(App->player->position.x, App->player->position.y);

	if (player_tiles_pos.x - enemy_tiles_pos.x <= 5 && player_tiles_pos.x - enemy_tiles_pos.x >= -5 && player_tiles_pos.y - enemy_tiles_pos.y <= 5 && player_tiles_pos.y - enemy_tiles_pos.y >= -5)
	{
		App->pathfinding->CreatePathManhattan(enemy_tiles_pos, player_tiles_pos, enemy_path);
		//originalpos = App->map->MapToWorld(enemy_tiles_pos.x, enemy_tiles_pos.y);
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


	if (i < enemy_path.Count()) { //enemy_path[i] != nullptr
		//No faltaba comprobar que enemy_path era null eso ya lo hace el count, el player entraba en la siguiente tile y ya te detectaba la comparacion pero se quedaba tocando
		// el iPoint tileInMap coje la posicion en el mapa de la tile para dirigir al enemigo hasta los puntos de la esquina opuesta asi hace el path bien y se queda dentro de la tile
		iPoint tileInMap = App->map->MapToWorld(enemy_path[i].x, enemy_path[i].y);
		if (isDead == true)
		{
			Dead();
		}

		else if (enemy_tiles_pos.y < enemy_path[i].y && position.y < tileInMap.y && movement[up] == true) {
			position.y += speed;
			current_in_path = true;
		}
		else if (enemy_tiles_pos.y > enemy_path[i].y && position.y > tileInMap.y && movement[down] == true) {
			position.y -= speed;
			current_in_path = true;
		}
		else if (enemy_tiles_pos.x <= enemy_path[i].x && position.x < tileInMap.x && movement[right] == true) {
			position.x += speed;
			animation = &walkRight;
			current_in_path = true;
		}
		else if (enemy_tiles_pos.x >= enemy_path[i].x && position.x > tileInMap.x && movement[left] == true) {
			position.x -= speed;
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


void Enemy_Fly::NormalizeAnimations(float dt) {

	// EXAMPLE

	walkLeft.speed = App->tex->NormalizeAnimSpeed("girl", "walkLeft", dt);
	walkRight.speed = App->tex->NormalizeAnimSpeed("girl", "walkRight", dt);
	deadLeft.speed = App->tex->NormalizeAnimSpeed("girl", "walkLeft", dt);
	deadRight.speed = App->tex->NormalizeAnimSpeed("girl", "walkRight", dt);

}

void Enemy_Fly::Dead()
{

	if (now == 0) {
		now = SDL_GetTicks();

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