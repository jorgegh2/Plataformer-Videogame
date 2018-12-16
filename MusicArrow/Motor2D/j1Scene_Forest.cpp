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
#include "j1Pathfinding.h"


j1Scene_Forest::j1Scene_Forest() : j1Module()
{
	name.create("scene_forest");
}

// Destructor
j1Scene_Forest::~j1Scene_Forest() {}

bool j1Scene_Forest::Awake(pugi::xml_node& config)
{
	App->map->Load(config.child("bgmusic").child("level1").attribute("source").as_string());
	enabled = false;
	active = false;
	return true;
}


// Called before the first frame
bool j1Scene_Forest::Start()
{
	App->map->Load("Level1.tmx");
	App->entities->player->Start();

	int w, h;
	uchar* data = NULL;
	if (App->map->CreateWalkabilityMap(w, h, &data))
		App->pathfinding->SetMap(w, h, data);
	RELEASE_ARRAY(data);
	
	return true;
}

// Called each loop iteration
bool j1Scene_Forest::Update(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_F4))
	{
		App->fadeToBlack->FadeToBlack(App->map_forest, App->map_winter);
		App->entities->player->ResetPlayer();
	}

	if (App->input->GetKey(SDL_SCANCODE_F11) == KEY_DOWN)
	{
		if (App->cap == 30)
			App->cap = 60;
		else
			App->cap = 30;
		App->capped_ms = 1000 / App->cap;
	}
	return true;
}

bool j1Scene_Forest::CleanUp()
{

	App->map->CleanUp();

	return true;
}
