#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1Scene.h"
#include "j1Collision.h"
#include "j1FadeToBlack.h"
#include "j1Scene_Forest.h"
#include "j1Scene_Winter.h"
#include "j1Player.h"
#include "j1Entities.h"

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	//App->map->Load("hello2.tmx");
	//App->map->Load("iso.tmx");

	//const char* path = "audio/music/PimPoy.wav";
	
	
	//j1Audio Mix_LoadWAV(const char *path);
	//App->audio->PlayMusic(path);
	/*if (a) level = "Level2.tmx";
	else level = "Level1.tmx";*/
	/*const char* level = "Level1.tmx";
	const char* level = "Level2.tmx";*/
	//App->map->Load("Level2.tmx"); 

	

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	if(App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		App->LoadGame("save_game.xml");

	if(App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		App->SaveGame("save_game.xml");

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y += 5;

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y -= 5;

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x += 5;

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x -= 5;
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		if (App->map_forest->active == true)
		{
			App->entities->player->ResetPlayer();
		}
		else
		{
			App->fadeToBlack->FadeToBlack(App->map_winter, App->map_forest);
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		
			App->entities->player->ResetPlayer();
		
	}

	App->map->Draw();

	
	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint map_coordinates = App->map->WorldToMap(x - App->render->camera.x, y - App->render->camera.y);
	p2SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d Tile:%d,%d",
					App->map->data.width, App->map->data.height,
					App->map->data.tile_width, App->map->data.tile_height,
					App->map->data.tilesets.count(),
					map_coordinates.x, map_coordinates.y);

	App->win->SetTitle(title.GetString());

	if (App->map_forest->active == true)
	{
		current_scene = App->map_forest->name.GetString();
	}
	else
	{
		current_scene = App->map_winter->name.GetString();
	}

	/*if (App->input->GetKey(SDL_SCANCODE_F4))
	{
		enabled = false;
		App->fadeToBlack->FadeToBlack(App->map, this);
		
	}*/

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}
// Load / Save
bool j1Scene::Load(pugi::xml_node& node)
{
	if (current_scene != node.child("level").attribute("current_scene").as_string())
	{
		if (current_scene == App->map_forest->name.GetString())
		{
			App->fadeToBlack->FadeToBlack(App->map_forest,App->map_winter);
		}
		else App->fadeToBlack->FadeToBlack(App->map_winter, App->map_forest);

	}
	return true;
}
bool j1Scene::Save(pugi::xml_node& node) const
{
	pugi::xml_node scene = node.append_child("level");

	if (App->map_forest->active == true)
	{
		scene.append_attribute("current_scene") = App->map_forest->name.GetString();
	}
	else
	{
		scene.append_attribute("current_scene") = App->map_winter->name.GetString();
	}
	return true;
}
