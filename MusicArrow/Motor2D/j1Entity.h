#ifndef __j1ENTITY_H__
#define __j1ENTITY_H__

#include "p2Point.h"
#include "Animation.h"
#include "PugiXml\src\pugixml.hpp"
#include "j1Collision.h"

struct SDL_Texture;
struct Collider;

enum Direction { up = 0, down, left, right, nextLevel, death };

class Entity
{
public:

	float gravity = 1.0f;
	float speed_jump = 0;
	fPoint speed = {0.0f, 0.0f};
	bool IsDeadEntity = false;

	


public:
	fPoint position;
	Animation* animation = nullptr;
	bool death = false;
	uint enemy;
	Collider* collider = nullptr;
	bool isPlayer;
	bool isDead = false;
	bool movement[4] = { true,true,true,true };
	int now = 0;

	AllDistance AllDistances;

public:
	Entity() {}
	Entity(int x, int y);
	virtual ~Entity();

	virtual bool Awake(pugi::xml_node&);
	virtual bool Start() { return true; };
	virtual bool Update(float dt) { return true; };
	virtual bool CleanUp() { return true; };

	virtual bool Load(pugi::xml_node&) { return true; };
	virtual bool Save(pugi::xml_node&) const { return true; };


	const Collider* GetCollider() const;
	virtual void NormalizeAnimations(float dt) {};
	virtual void CalculateGravity(float dt) {};
	virtual void Move(float dt) {};
	virtual void Draw(SDL_Texture* sprites);
	virtual void OnCollision(Collider* collider);
	virtual void Dead() { };
};

#endif

