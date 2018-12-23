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
#include "Enemy_Tree.h"
#include "j1Entity.h"
#include "j1Entities.h"
#include "Brofiler/Brofiler.h"

Enemy_Tree::Enemy_Tree(int x, int y, SDL_Rect colliderRect) : Entity(x, y)
{

	
	walk = App->tex->CreateAnimation("tree", "walk", true);
	

	tree_sound = App->audio->LoadFx("audio/fx/tree.wav");

	originalpos.x = position.x = x;
	originalpos.y = position.y = y;


	collider = App->collision->AddCollider(colliderRect, COLLIDER_ENEMY, App->entities);
	timer.Reset();
}

void Enemy_Tree::Move(float dt)
{
	BROFILER_CATEGORY("Enemy_TreeMove", Profiler::Color::Gray);
	animation = &walk;
	NormalizeAnimations(dt);


	speed.x = 200 * dt;
	speed.y = 200 * dt;

	if(App->entities->player->position.x - position.x > 0)
	position.x -= speed.x;

	CalculateGravity(dt);
}

void Enemy_Tree::CalculateGravity(float dt)
{
	BROFILER_CATEGORY("CalculateGravityEnemy", Profiler::Color::Gray);

	if (speed_jump < 20)
	{
		speed_jump += gravity;
	}
	else
	{
		speed_jump = 20;
	}

	if (speed_jump < AllDistances.distancePositiveY.Modulo)
		position.y += speed_jump;
	else
		position.y += AllDistances.distancePositiveY.Modulo;

	if (movement[down] == false && speed_jump > 0)
	{
		speed_jump = 0;
	}

}

void Enemy_Tree::NormalizeAnimations(float dt)
{
	BROFILER_CATEGORY("NormalizeAnimationsEnemy", Profiler::Color::Gray);

	walk.speed = App->tex->NormalizeAnimSpeed("tree", "walk", dt);


}



bool Enemy_Tree::Save(pugi::xml_node& data) const
{
	BROFILER_CATEGORY("SaveEnemyTree", Profiler::Color::Gray);
	pugi::xml_node enemy_tree_node = data.append_child("enemytree");

	pugi::xml_node pos_node = enemy_tree_node.append_child("position");

	pos_node.append_attribute("x") = position.x;
	pos_node.append_attribute("y") = position.y;

	pugi::xml_node speed_node = enemy_tree_node.append_child("speed");

	speed_node.append_attribute("x") = speed.x;
	speed_node.append_attribute("y") = speed.y;

	pugi::xml_node speed_jump_node = enemy_tree_node.append_child("speedjump");

	speed_jump_node.append_attribute("speedjump") = speed_jump;

	pugi::xml_node gravity_node = enemy_tree_node.append_child("gravity");

	gravity_node.append_attribute("gravity") = gravity;

	pugi::xml_node dead_node = enemy_tree_node.append_child("isDead");

	dead_node.append_attribute("isDead") = isDead;

	pugi::xml_node now_node = enemy_tree_node.append_child("now");

	now_node.append_attribute("now") = now;

	return true;
}

bool Enemy_Tree::Load(pugi::xml_node& data)
{
	BROFILER_CATEGORY("LoadEnemy", Profiler::Color::Gray);
	//load player position
	position.x = data.child("enemytree").child("position").attribute("x").as_int();
	position.y = data.child("enemytree").child("position").attribute("y").as_int();

	//load speed position
	speed.x = data.child("enemytree").child("speed").attribute("x").as_int();
	speed.y = data.child("enemytree").child("speed").attribute("y").as_int();

	//load speed jump
	speed_jump = data.child("enemytree").child("speedjump").attribute("speedjump").as_int();

	//load gravity
	speed_jump = data.child("enemytree").child("gravity").attribute("gravity").as_int();

	//load dead state
	isDead = data.child("enemytree").child("isDead").attribute("isDead").as_bool();

	//load now
	now = data.child("enemytree").child("now").attribute("now").as_int();

	return true;
}