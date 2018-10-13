#ifndef __j1Collision_H__
#define __j1Collision_H__

#define MAX_COLLIDERS 450

#include "j1Module.h"

enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,
	COLLIDER_FLOOR,
	COLLIDER_PLATAFORM,
	COLLIDER_WATER,
	COLLIDER_START_WALL,
	COLLIDER_FINISH_LEVEL,
	COLLIDER_PLAYER,


	COLLIDER_MAX
};
struct Distance
{
	COLLIDER_TYPE nearestColliderType;
	float Modulo;
	bool positiveX = false;
	bool negativeX = false;
	bool positiveY = false;
	bool negativeY = false;
};
struct Collider
{
	SDL_Rect rect;
	bool to_delete = false;
	COLLIDER_TYPE type;
	j1Module* callback = nullptr;

	Collider(SDL_Rect rectangle, COLLIDER_TYPE type, j1Module* callback = nullptr) :
		rect(rectangle),
		type(type),
		callback(callback)
	{}
	int type_collider;
	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}

	bool CheckCollision(const SDL_Rect& r) const;
	Distance DistanceToNearestCollider(SDL_Rect& collider_rect, COLLIDER_TYPE& collider_type) const;
	
};



class j1Collision : public j1Module
{
public:

	j1Collision();
	~j1Collision();

	bool PreUpdate() override;
	bool Update(float dt) override;
	bool CleanUp() override;

	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type, j1Module* callback = nullptr);
	void DebugDraw();

	Distance distance;
	Distance dNegativeX;
	Distance dPositiveX;
	Distance dNegativeY;
	Distance dPositiveY;
	COLLIDER_TYPE collider_type;
//	Distance FinalDistance;
	
	

private:

	Collider * colliders[MAX_COLLIDERS];
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
	bool debug = false;
	COLLIDER_TYPE DefineType(int type_as_int);
};

#endif // __j1Collision_H__
