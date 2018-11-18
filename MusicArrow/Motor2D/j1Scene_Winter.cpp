#include "j1Scene_Forest.h"
#include "j1Scene_Winter.h"
#include "j1Map.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1FadeToBlack.h"
#include "j1Render.h"
#include "j1Scene.h"
#include "j1Player.h"
#include "j1Entities.h"

j1Scene_Winter::j1Scene_Winter()
{
	name.create("scene_winter");
}


 //Destructor
j1Scene_Winter::~j1Scene_Winter() {}

bool j1Scene_Winter::Awake(pugi::xml_node& node)
{
	App->map->Load(node.child("bgmusic").child("level2").attribute("source").as_string());
	enabled = false;
	active = false;
	return true;
}



// Called before the first frame
bool j1Scene_Winter::Start()
{
	App->map->Load("Level2.tmx");
	
	return true;
}

// Called each loop iteration
bool j1Scene_Winter::Update(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_F4))
	{
		App->fadeToBlack->FadeToBlack(App->map_winter, App->map_forest);
		App->entities->player->ResetPlayer();
	}
	return true;
}

bool j1Scene_Winter::CleanUp()
{

	App->map->CleanUp();

	return true;
}
