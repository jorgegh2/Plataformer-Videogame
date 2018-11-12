#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Player.h"
#include "j1Entities.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Entity.h"
#include "Enemy_Fly.h"
#include "j1Map.h"
#include "Enemy_Walk.h"
#include "p2Log.h"
#include "Brofiler\Brofiler.h"
#include "Coin.h"
#include "j1FadeToBlack.h"
#include "j1Collision.h"

#define SPAWN_MARGIN 140
#define DESPAWN_MARGIN 1400

j1Entities::j1Entities()
{
	for (uint i = 0; i < MAX_ENTITIES; ++i)
		entities[i] = nullptr;

	name.create("entities");
}

// Destructor
j1Entities::~j1Entities()
{
	App->tex->UnLoad(sprites);
}

bool j1Entities::Start()
{
	// Create a prototype for each enemy available so we can copy them around
	sprites = App->tex->Load("maps/enemySprites.png");
	player_life = 3;
	return true;
}

bool j1Entities::Awake(pugi::xml_node& config)
{
	return true;

}
bool j1Entities::PreUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (queue[i].type != ENTITY_TYPES::NO_TYPE)
		{

			if (queue[i].x < (App->render->camera.x - (App->render->camera.w) - SPAWN_MARGIN)*(-1))
			{
				SpawnEntity(queue[i]);
				queue[i].type = ENTITY_TYPES::NO_TYPE;
				LOG("Spawning enemy at %i %i", queue[i].x, queue[i].y);
			}
		}
	}


	return true;
}

// Called before render is available
bool j1Entities::Update(float dt)
{

	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i] != nullptr)
		{
			entities[i]->Move(dt);
		}
	}


	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i] != nullptr)
		{
			entities[i]->Draw(sprites);
		}
	}
	//REVISAR: YA SE NORMALIZA EN CADA CLASE Y si se hace deberia de ser antes de mover
	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i] != nullptr)
		{
			entities[i]->NormalizeAnimations(dt);
		}
	}

	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i] != nullptr)
		{
			if (entities[i]->death == true && entities[i]->isPlayer == false) {
				delete entities[i];
				entities[i] = nullptr;
			}
		}
	}

	return true;
}

bool j1Entities::PostUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i] != nullptr)
		{
			if (entities[i]->position.x < (App->render->camera.x + DESPAWN_MARGIN)*(-1))
			{

				delete entities[i];
				entities[i] = nullptr;
			}
		}
	}

	return true;
}

// Called before quitting
bool j1Entities::CleanUp()
{
	App->tex->UnLoad(sprites);
	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i] != nullptr)
		{
			delete entities[i];
			entities[i] = nullptr;
		}
	}

	return true;
}

bool j1Entities::ResetEntities()
{

	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i] != nullptr)
		{
			entities[i]->collider->to_delete = true;
			entities[i]->isPlayer;
			delete entities[i];
			entities[i] = nullptr;
		}
	}

	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (queue[i].type != NULL)
			queue[i].type = NO_TYPE;
		queue[i].x = 0;
		queue[i].y = 0;
	}


	return true;

}

bool j1Entities::AddEntity(ENTITY_TYPES type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (queue[i].type == ENTITY_TYPES::NO_TYPE)
		{
			App->map->data.tile_height;
			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
			ret = true;

			break;
		}
	}

	return ret;
}

void j1Entities::SpawnEntity(const EntityInfo& info)
{
	// find room for the new enemy
	uint i = 0;
	for (; entities[i] != nullptr && i < MAX_ENTITIES; ++i);

	if (i != MAX_ENTITIES)
	{
		switch (info.type)
		{

		case ENTITY_TYPES::NO_TYPE:
			//enemies[i] = new Enemy_Balloon(info.x, info.y);
			break;

		case ENTITY_TYPES::ENEMY_FLY:
			entities[i] = new Enemy_Fly(info.x, info.y);
			break;
		case ENTITY_TYPES::ENEMY_WALK:
			entities[i] = new Enemy_Walk(info.x, info.y);
			break;
		case ENTITY_TYPES::ENTITY_PLAYER:
			//entities[i] = player = new j1Player(info.x,info.y);
			entities[i]->isPlayer = true;
			break;
		case ENTITY_TYPES::COIN:
			entities[i] = new Coin(info.x, info.y);
			break;
		}

	}
}

void j1Entities::OnCollision(Collider* c1, Collider* c2)
{

}

