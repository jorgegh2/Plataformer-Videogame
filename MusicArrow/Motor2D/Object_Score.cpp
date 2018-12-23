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
#include "Object_Score.h"
#include "j1Entity.h"
#include "j1Entities.h"
#include "Brofiler/Brofiler.h"

Object_Score::Object_Score(int x, int y, SDL_Rect colliderRect) : Entity(x, y)
{

	coin_sound = App->audio->LoadFx("audio/fx/coin.wav");

	originalpos.x = position.x = x;
	originalpos.y = position.y = y;

	collider = App->collision->AddCollider(colliderRect, COLLIDER_OBJECT, App->entities);
}

void Object_Score::Move(float dt)
{
	BROFILER_CATEGORY("Object_ScoreMove", Profiler::Color::Gray);
	
}


bool Object_Score::Save(pugi::xml_node& data) const
{
	BROFILER_CATEGORY("SaveObject_Score", Profiler::Color::Gray);

	pugi::xml_node enemy_score_node = data.append_child("enemyscore");

	pugi::xml_node pos_node = enemy_score_node.append_child("position");

	pos_node.append_attribute("x") = position.x;
	pos_node.append_attribute("y") = position.y;

	pugi::xml_node dead_node = enemy_score_node.append_child("isDead");

	dead_node.append_attribute("isDead") = isDead;

	return true;
}

bool Object_Score::Load(pugi::xml_node& data)
{
	BROFILER_CATEGORY("LoadEnemy", Profiler::Color::Gray);
	//load player position
	position.x = data.child("enemyscore").child("position").attribute("x").as_int();
	position.y = data.child("enemyscore").child("position").attribute("y").as_int();

	//load dead state
	isDead = data.child("enemyscore").child("isDead").attribute("isDead").as_bool();

	return true;
}