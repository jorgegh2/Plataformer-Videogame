#include "j1Scene_Forest.h"
#include "j1Scene_Winter.h"
#include "j1Map.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1FadeToBlack.h"
#include "j1Render.h"
#include "j1Scene.h"

j1Scene_Forest::j1Scene_Forest() : j1Module()
{
	//name.create("scene_forest");
	
}

// Destructor
j1Scene_Forest::~j1Scene_Forest() {}



// Called before the first frame
bool j1Scene_Forest::Start()
{
	App->map->Load("Level1.tmx");
	App->map->SetAllColliders();
	return true;
}

// Called each loop iteration
bool j1Scene_Forest::Update(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_F4))
	{
		App->fadeToBlack->FadeToBlack(App->map_forest, App->map_winter);
	}
	return true;
}

bool j1Scene_Forest::CleanUp()
{

	App->map->CleanUp();

	return true;
}
