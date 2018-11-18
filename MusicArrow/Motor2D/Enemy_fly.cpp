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

Enemy_Fly::Enemy_Fly(int x, int y) : Entity(x, y)
{

	fly = App->tex->CreateAnimation("crow", "fly", true);
	attack = App->tex->CreateAnimation("crow", "attack", true);

	flysound = App->audio->LoadFx("audio/fx/glide.wav");
	animation = &fly;

	originalpos.x = position.x = x;
	originalpos.y = position.y = y;

	//App->entities posible error, original(App->entity)
	collider = App->collision->AddCollider({ (int)position.x, (int)position.y + 10, 80, 80 }, COLLIDER_WATER, App->entities);
}

void Enemy_Fly::Move(float dt)
{
	if (isDead == false)
		//isDead = App->collision->CollisionToWorld(collider, movement);
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
		//App->pathfinding->CreatePathManhattan(enemy_tiles_pos, player_tiles_pos, enemy_path);
		//originalpos = App->map->MapToWorld(enemy_tiles_pos.x, enemy_tiles_pos.y);
	}
	else {

		if (timer.Read() > 2000) {

			if (movingLeft) {
				movingLeft = false;
				timer.Reset();
				animation = &fly;
			}
			
		}
		//if (movingLeft)
			//App->pathfinding->CreatePathManhattan(enemy_tiles_pos, { enemy_tiles_pos.x + 1 , enemy_tiles_pos.y }, enemy_path);
		//else
			//App->pathfinding->CreatePathManhattan(enemy_tiles_pos, { enemy_tiles_pos.x - 1 , enemy_tiles_pos.y }, enemy_path);
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