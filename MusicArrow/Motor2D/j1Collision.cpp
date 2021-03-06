#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Collision.h"
#include "j1Map.h"
#include <iostream>
#include "p2Log.h"
#include "Brofiler\Brofiler.h"

j1Collision::j1Collision() : j1Module()
{
	name.create("collision");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[COLLIDER_FLOOR][COLLIDER_FLOOR] = false;
	matrix[COLLIDER_FLOOR][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_FLOOR][COLLIDER_PLATAFORM] = false;
	matrix[COLLIDER_FLOOR][COLLIDER_WATER] = false;
	matrix[COLLIDER_FLOOR][COLLIDER_START_WALL] = false;
	matrix[COLLIDER_FLOOR][COLLIDER_FINISH_LEVEL] = false;
	matrix[COLLIDER_FLOOR][COLLIDER_ENEMY] = true;


	matrix[COLLIDER_PLAYER][COLLIDER_FLOOR] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_PLATAFORM] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_WATER] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_START_WALL] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_FINISH_LEVEL] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY] = true;


	matrix[COLLIDER_ENEMY][COLLIDER_FLOOR] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLATAFORM] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_WATER] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_START_WALL] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_FINISH_LEVEL] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY] = false;


	matrix[COLLIDER_PLATAFORM][COLLIDER_FLOOR] = false;
	matrix[COLLIDER_PLATAFORM][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_PLATAFORM][COLLIDER_PLATAFORM] = false;
	matrix[COLLIDER_PLATAFORM][COLLIDER_WATER] = false;
	matrix[COLLIDER_PLATAFORM][COLLIDER_START_WALL] = false;
	matrix[COLLIDER_PLATAFORM][COLLIDER_FINISH_LEVEL] = false;
	matrix[COLLIDER_PLATAFORM][COLLIDER_ENEMY] = true;


	matrix[COLLIDER_WATER][COLLIDER_FLOOR] = false;
	matrix[COLLIDER_WATER][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_WATER][COLLIDER_PLATAFORM] = false;
	matrix[COLLIDER_WATER][COLLIDER_WATER] = false;
	matrix[COLLIDER_WATER][COLLIDER_START_WALL] = false;
	matrix[COLLIDER_WATER][COLLIDER_FINISH_LEVEL] = false;
	matrix[COLLIDER_WATER][COLLIDER_ENEMY] = true;


	matrix[COLLIDER_START_WALL][COLLIDER_FLOOR] = false;
	matrix[COLLIDER_START_WALL][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_START_WALL][COLLIDER_PLATAFORM] = false;
	matrix[COLLIDER_START_WALL][COLLIDER_WATER] = false;
	matrix[COLLIDER_START_WALL][COLLIDER_START_WALL] = false;
	matrix[COLLIDER_START_WALL][COLLIDER_FINISH_LEVEL] = false;
	matrix[COLLIDER_START_WALL][COLLIDER_ENEMY] = true;
	

	matrix[COLLIDER_FINISH_LEVEL][COLLIDER_FLOOR] = false;
	matrix[COLLIDER_FINISH_LEVEL][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_FINISH_LEVEL][COLLIDER_PLATAFORM] = false;
	matrix[COLLIDER_FINISH_LEVEL][COLLIDER_WATER] = false;
	matrix[COLLIDER_FINISH_LEVEL][COLLIDER_START_WALL] = false;
	matrix[COLLIDER_FINISH_LEVEL][COLLIDER_FINISH_LEVEL] = false;
	matrix[COLLIDER_FINISH_LEVEL][COLLIDER_ENEMY] = true;
	
}

// Destructor
j1Collision::~j1Collision()
{}

bool j1Collision::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->to_delete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	// Calculate collisions
	Collider* c1;
	Collider* c2;
	AllDistances.distanceNegativeX.Modulo = 10000;
	AllDistances.distancePositiveX.Modulo = 10000;
	AllDistances.distanceNegativeY.Modulo = 10000;
	AllDistances.distancePositiveY.Modulo = 10000;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (c1->CheckCollision(c2->rect) == true)
			{
				if (matrix[c1->type][c2->type] && c1->callback)
					c1->callback->OnCollision(c1, c2);

				if (matrix[c2->type][c1->type] && c2->callback)
					c2->callback->OnCollision(c2, c1);
			}
			/*if (c2->type == COLLIDER_PLAYER)
			{

				CalculateAllDistance(c1, c2, AllDistances);

			}*/

		}
	}

	return true;
}

// Called before render is available
bool j1Collision::Update(float dt)
{
	BROFILER_CATEGORY("UpdateCollision", Profiler::Color::PapayaWhip);

	DebugDraw();

	return true;
}

void j1Collision::DebugDraw()
{
	BROFILER_CATEGORY("DebugDraw", Profiler::Color::PapayaWhip);
	if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
		debug = !debug;

	if (debug == false)
		return;

	Uint8 alpha = 60;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
			continue;

		switch (colliders[i]->type)
		{
		case COLLIDER_NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case COLLIDER_FLOOR: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case COLLIDER_PLAYER: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break; 
		case COLLIDER_ENEMY: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case COLLIDER_OBJECT: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 255, alpha);
			break;
		case COLLIDER_PLATAFORM: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
		case COLLIDER_WATER: // cian
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		case COLLIDER_START_WALL: // magenta
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 204, alpha);
			break;
		case COLLIDER_FINISH_LEVEL: // magenta
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 204, alpha);
			break;		
		}
	}
}

// Called before quitting
bool j1Collision::CleanUp()
{
	BROFILER_CATEGORY("CleanUpCollision", Profiler::Color::PapayaWhip);
	LOG("Freeing all colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* j1Collision::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, j1Module* callback)
{
	BROFILER_CATEGORY("AddCollider", Profiler::Color::PapayaWhip);
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, callback);
			break;
		}
	}

	return ret;
}


// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	BROFILER_CATEGORY("CheckCollision", Profiler::Color::PapayaWhip);
	if ((r.x + r.w <= rect.x) || (r.x >= rect.x + rect.w) || (r.y + r.h <= rect.y) || (r.y >= rect.y + rect.h)) return false;
	else return true;
}

COLLIDER_TYPE j1Collision::DefineType(int type_as_int)
{
	switch (type_as_int)
	{
	case 0:
		return COLLIDER_FLOOR;
	case 1:
		return COLLIDER_PLATAFORM;
	case 2:
		return COLLIDER_WATER;
	case 3:
		return COLLIDER_START_WALL;
	case 4:
		return COLLIDER_FINISH_LEVEL;
	case 5:
		return COLLIDER_PLAYER;
	case 6:
		return COLLIDER_ENEMY;
	case 7:
		return COLLIDER_OBJECT;
	default:
		return COLLIDER_NONE;
	}
}
Distance Collider::DistanceToNearestCollider(SDL_Rect& collider_rect, COLLIDER_TYPE& collider_type) const
{
	BROFILER_CATEGORY("DistanceToNearestCollider", Profiler::Color::PapayaWhip);
	Distance ret;
	ret.nearestColliderType = collider_type;
	ret.Modulo = 10000;
	if (collider_rect.x + collider_rect.w <= rect.x)
	{
		if (collider_rect.y + collider_rect.h > rect.y && collider_rect.y < rect.y + rect.h)
		{
			ret.negativeX = true;
			ret.negativeY = false;
			ret.positiveX = false;
			ret.positiveY = false;
			ret.Modulo = rect.x - (collider_rect.x + collider_rect.w);
		}
	}
	if (collider_rect.x >= rect.x + rect.w)
	{
		if (collider_rect.y + collider_rect.h > rect.y && collider_rect.y < rect.y + rect.h)
		{
			ret.positiveX = true;
			ret.negativeX = false;
			ret.negativeY = false;
			ret.positiveY = false;
			ret.Modulo = collider_rect.x - (rect.x + rect.w);
		}
	}
	if (collider_rect.y + collider_rect.h <= rect.y)
	{
		if (collider_rect.x + collider_rect.w > rect.x && collider_rect.x < rect.x + rect.w)
		{
			ret.negativeY = true;
			ret.positiveX = false;
			ret.positiveY = false;
			ret.negativeX = false;
			ret.Modulo = rect.y - (collider_rect.y + collider_rect.h);
		}
	}
	if (collider_rect.y >= rect.y + rect.h)
	{
		
		if (collider_rect.x + collider_rect.w > rect.x && collider_rect.x < rect.x + rect.w)
		{
			ret.positiveY = true;
			ret.negativeX = false;
			ret.negativeY = false;
			ret.positiveX = false;
			ret.Modulo = collider_rect.y - (rect.y + rect.h);
		}
	}

	return ret;
}

void j1Collision::AllCollidersToDelete()
{
	BROFILER_CATEGORY("AllCollidersToDelete", Profiler::Color::PapayaWhip);
	for (uint i = 0; i < MAX_COLLIDERS; i++)
	{
		if(colliders[i] != nullptr)
		{
			colliders[i]->to_delete = true;
		}
	}
}
void j1Collision::CalculateAllDistance(Collider* c1, Collider* c2, AllDistance& Alldistances)
{
	
	Distance distance = c2->DistanceToNearestCollider(c1->rect, c1->type);
	//if (i == 0) FinalDistance = distance;
	if (distance.negativeX && distance.Modulo < Alldistances.distanceNegativeX.Modulo)
	{
		Alldistances.distanceNegativeX.Modulo = distance.Modulo;
		Alldistances.distanceNegativeX.nearestColliderType = distance.nearestColliderType;
	}
	else if (distance.positiveX && distance.Modulo < Alldistances.distancePositiveX.Modulo)
	{
		Alldistances.distancePositiveX.Modulo = distance.Modulo;
		Alldistances.distancePositiveX.nearestColliderType = distance.nearestColliderType;
	}
	else if (distance.negativeY && distance.Modulo < Alldistances.distanceNegativeY.Modulo)
	{
		Alldistances.distanceNegativeY.Modulo = distance.Modulo;
		Alldistances.distanceNegativeY.nearestColliderType = distance.nearestColliderType;
	}
	else if (distance.positiveY && distance.Modulo < Alldistances.distancePositiveY.Modulo)
	{
		Alldistances.distancePositiveY.Modulo = distance.Modulo;
		Alldistances.distancePositiveY.nearestColliderType = distance.nearestColliderType;
	}

}

void j1Collision::CalculateCollision(AllDistance& AllDistances, Collider* colliderEntity)
{
	// Calculate collisions
	Collider* c1;
	AllDistances.distanceNegativeX.Modulo = 10000;
	AllDistances.distancePositiveX.Modulo = 10000;
	AllDistances.distanceNegativeY.Modulo = 10000;
	AllDistances.distancePositiveY.Modulo = 10000;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		CalculateAllDistance(c1, colliderEntity, AllDistances);
		
	}
}




