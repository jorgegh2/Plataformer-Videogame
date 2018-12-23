#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Player.h"
#include "j1Entities.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Entity.h"
#include "j1Window.h"
#include "Enemy_Fly.h"
#include "j1Map.h"
#include "Enemy_Walk.h"
#include "Enemy_Tree.h"
#include "Object_Coin.h"
#include "p2Log.h"
#include "Brofiler\Brofiler.h"
#include "j1FadeToBlack.h"
#include "j1Collision.h"

#define SPAWN_MARGIN 300
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
	
}

bool j1Entities::Start()
{

	sprites = App->tex->Load("assets/Enemies/enemies_spritesheet.png");

	return true;
}

bool j1Entities::Awake(pugi::xml_node& config) 
{

	this->config = config;

	return true;

}
bool j1Entities::PreUpdate()
{
	BROFILER_CATEGORY("PreUpdateEntities", Profiler::Color::Pink);

	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (queue[i].type != ENTITY_TYPES::NO_TYPE)
		{

			if (queue[i].x * App->win->GetScale() < (App->render->camera.x - (App->render->camera.w) - SPAWN_MARGIN)*(-1))
			{
				SpawnEntity(queue[i]);
				queue[i].type = ENTITY_TYPES::NO_TYPE;
				LOG("Spawning enemy at %i %i", queue[i].x, queue[i].y);
			}
		}
	}

	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i] != nullptr)
		{
			App->collision->CalculateCollision(entities[i]->AllDistances, entities[i]->collider);
		}
	}


	return true;
}

// Called before render is available
bool j1Entities::Update(float dt)
{
	BROFILER_CATEGORY("UpdateEntities", Profiler::Color::Pink);
	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i] != nullptr)
		{
			entities[i]->Update(dt);
		}
	}

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
	
	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i] != nullptr)
		{
			entities[i]->NormalizeAnimations(dt);
		}
	}

	return true;
}

bool j1Entities::PostUpdate()
{
	BROFILER_CATEGORY("PostUpdateEntities", Profiler::Color::Pink);

	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i] != nullptr)
		{
			if (entities[i]->position.x * App->win->GetScale() < (App->render->camera.x + DESPAWN_MARGIN)*(-1) || entities[i]->death == true)
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
	BROFILER_CATEGORY("CleanUpEntities", Profiler::Color::Pink);
	//App->tex->UnLoad(sprites);
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
	BROFILER_CATEGORY("ResetEntities", Profiler::Color::Pink);
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

bool j1Entities::AddEntity(ENTITY_TYPES type, int x, int y, SDL_Rect colliderRect)
{
	BROFILER_CATEGORY("AddEntity", Profiler::Color::Pink);
	bool ret = false;

	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (queue[i].type == ENTITY_TYPES::NO_TYPE)
		{
			
			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
			queue[i].colliderRect = colliderRect;
			ret = true;
			if (type == ENTITY_PLAYER)
			{
				SpawnEntity(queue[i]); // The player
				queue[i].type = ENTITY_TYPES::NO_TYPE;
			}
			break;
		}
	}

	return ret;
}

void j1Entities::SpawnEntity(const EntityInfo& info)
{
	BROFILER_CATEGORY("SpawnEntity", Profiler::Color::Pink);

	// find room for the new enemy
	uint i = 0;
	for (; entities[i] != nullptr && i < MAX_ENTITIES; ++i);

	if (i != MAX_ENTITIES)
	{
		switch (info.type)
		{

		case ENTITY_TYPES::NO_TYPE:
			
			break;

		case ENTITY_TYPES::ENEMY_FLY:
			entities[i] = new Enemy_Fly(info.x, info.y, info.colliderRect);
			break;
		case ENTITY_TYPES::ENEMY_WALK:
			entities[i] = new Enemy_Walk(info.x, info.y, info.colliderRect);
			break;
		case ENTITY_TYPES::ENEMY_BALL:
			entities[i] = new Enemy_Walk(info.x, info.y, info.colliderRect);
			break;
		case ENTITY_TYPES::ENEMY_TREE:
			entities[i] = new Enemy_Tree(info.x, info.y, info.colliderRect);
			break;
		case ENTITY_TYPES::ENTITY_PLAYER:
			entities[i] = player = new j1Player(info.x,info.y, info.colliderRect);
			entities[i]->isPlayer = true;
			break;
		case ENTITY_TYPES::OBJECT_COIN:
			entities[i] = new Object_Coin(info.x, info.y, info.colliderRect);
			break;
		}

		entities[i]->Awake(config);

	}
}


bool j1Entities::Load(pugi::xml_node& data)
{
	BROFILER_CATEGORY("LoadEntities", Profiler::Color::Pink);

	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i] != nullptr)
		{
			entities[i]->Load(data);
		}
	}

	return true;
}

bool j1Entities::Save(pugi::xml_node& data) const
{
	BROFILER_CATEGORY("SaveEntities", Profiler::Color::Pink);

	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i] != nullptr)
		{
			entities[i]->Save(data);
		}
	}

	return true;
}

