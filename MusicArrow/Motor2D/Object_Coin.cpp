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
#include "p2DynArray.h"
#include "Object_Coin.h"
#include "j1Entity.h"
#include "j1Entities.h"
#include "Brofiler/Brofiler.h"

Object_Coin::Object_Coin(int x, int y, SDL_Rect colliderRect) : Entity(x, y)
{

	idle = App->tex->CreateAnimation("coin", "idle", true);


	coin_sound = App->audio->LoadFx("audio/fx/coin.wav");

	originalpos.x = position.x = x;
	originalpos.y = position.y = y;


	collider = App->collision->AddCollider(colliderRect, COLLIDER_OBJECT, App->entities);
	timer.Reset();
}

void Object_Coin::Move(float dt)
{
	BROFILER_CATEGORY("Object_CoinMove", Profiler::Color::Gray);
	animation = &idle;
}


void Object_Coin::NormalizeAnimations(float dt)
{
	BROFILER_CATEGORY("NormalizeAnimationsEnemy", Profiler::Color::Gray);

	idle.speed = App->tex->NormalizeAnimSpeed("coin", "idle", dt);


}

bool Object_Coin::Save(pugi::xml_node& data) const
{
	BROFILER_CATEGORY("SaveObject_Coin", Profiler::Color::Gray);

	pugi::xml_node enemy_coin_node = data.append_child("enemycoin");

	pugi::xml_node pos_node = enemy_coin_node.append_child("position");

	pos_node.append_attribute("x") = position.x;
	pos_node.append_attribute("y") = position.y;

	pugi::xml_node dead_node = enemy_coin_node.append_child("isDead");

	dead_node.append_attribute("isDead") = isDead;

	return true;
}

bool Object_Coin::Load(pugi::xml_node& data)
{
	BROFILER_CATEGORY("LoadEnemy", Profiler::Color::Gray);
	//load player position
	position.x = data.child("enemycoin").child("position").attribute("x").as_int();
	position.y = data.child("enemycoin").child("position").attribute("y").as_int();

	//load dead state
	isDead = data.child("enemycoin").child("isDead").attribute("isDead").as_bool();

	return true;
}