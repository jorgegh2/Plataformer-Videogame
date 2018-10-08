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

<<<<<<< HEAD
	App->map->Load("test128-2.tmx");
	
=======
	App->map->Load("test128-2.tmx"); //DONT WORK CAUSE THE INTERN STRUCTURE IS DIFFERENT!!
	p2List_item<MapObjects*>* item_object = nullptr;
	for (item_object = App->map->data.objects.start; item_object; item_object = item_object->next)
	{
		App->collision->AddCollider(item_object->data->RectCollider, COLLIDER_WALL, nullptr);
	}

	/*
	uint id = 0;
	for (item_tileset = data.tilesets.end; item_tileset; item_tileset = item_tileset->prev) {
		for (item_layer = data.layers.start; item_layer; item_layer = item_layer->next) {
			for (uint i = 0; i < item_layer->data->height; i++) {
				for (uint j = 0; j < item_layer->data->width; j++) {
					id = item_layer->data->data[item_layer->data->Get(j, i)];
					if (id != 0)
						App->render->Blit(item_tileset->data->texture, MapToWorld(j, i).x, MapToWorld(j, i).y, &item_tileset->data->GetTileRect(id));
				}
			}
		}
	}*/

>>>>>>> c0e7b84441da004586afbb85fb2d4c3c21255d36
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
	if(App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		App->LoadGame("save_game.xml");

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		App->SaveGame("save_game.xml");

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y += 1;

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y -= 1;

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x += 1;

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x -= 1;

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
