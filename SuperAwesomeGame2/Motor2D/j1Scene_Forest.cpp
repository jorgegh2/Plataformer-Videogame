#include "j1Scene_Forest.h"
#include "j1Map.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1FadeToBlack.h"
#include "j1Render.h"

j1Scene_Forest::j1Scene_Forest() 
{
	name.create("scene_forest");
}

	// Destructor
j1Scene_Forest::~j1Scene_Forest() {}

	// Called before render is available
bool j1Scene_Forest::Awake() 
{
	return true;
}

	// Called before the first frame
	bool j1Scene_Forest::Start()
	{
		App->map->Load("Level2.tmx");
		App->scene->SetAllColliders();
	}

	// Called each loop iteration
	bool j1Scene_Forest::Update(float dt) 
	{
		j1Scene::Update(dt);

		if (App->input->GetKey(SDL_SCANCODE_F4))
		{
			App->fadeToBlack->FadeToBlack(this, App->);
		}
	}
