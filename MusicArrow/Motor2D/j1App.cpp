#include <iostream> 
#include <sstream> 

#include "p2Defs.h"
#include "p2Log.h"

#include "j1Window.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Scene.h"
#include "j1Map.h"
#include "j1Collision.h"
#include "j1App.h"
#include "j1FadeToBlack.h"
#include "j1Player.h"
#include "Time.h"
#include "j1Scene_Forest.h"
#include "j1Scene_Winter.h"
#include "j1Entities.h"
#include "j1Pathfinding.h"
#include "j1PerfTimer.h"
#include "j1Fonts.h"
#include "j1Gui.h"
#include "Brofiler/Brofiler.h"

// Constructor
j1App::j1App(int argc, char* args[]) : argc(argc), args(args)
{
	dt = 0.0f;
	frames = 0;
	want_to_save = want_to_load = false;

	input = new j1Input();
	win = new j1Window();
	render = new j1Render();
	tex = new j1Textures();
	audio = new j1Audio();
	scene = new j1Scene();
	map = new j1Map();
	collision = new j1Collision();
	fadeToBlack = new j1FadeToBlack();
	time = new Timer();
	map_forest = new j1Scene_Forest();
	map_winter = new j1Scene_Winter();
	entities = new j1Entities();
	pathfinding = new j1PathFinding();
	font = new j1Fonts();
	gui = new j1Gui();

	AddModule(input);
	AddModule(win);
	AddModule(tex);
	AddModule(audio);
	AddModule(map);
	
	AddModule(fadeToBlack);
	AddModule(collision);
	
	AddModule(pathfinding);
	AddModule(font);
	AddModule(gui);

	// scene last
	AddModule(scene);
	AddModule(map_forest);
	AddModule(map_winter);
	AddModule(entities);

	// render last to swap buffer
	AddModule(render);
}

// Destructor
j1App::~j1App()
{
	// release modules
	p2List_item<j1Module*>* item = modules.end;

	while (item != NULL)
	{
		RELEASE(item->data);
		item = item->prev;
	}

	modules.clear();
}

void j1App::AddModule(j1Module* module)
{
	module->Init();
	modules.add(module);
}

// Called before render is available
bool j1App::Awake()
{
	

	bool ret = false;

	config = LoadConfig(config_file);

	if (config.empty() == false)
	{
		ret = true;
		app_config = config.child("app");
		title.create(app_config.child("title").child_value());
		organization.create(app_config.child("organization").child_value());
	}

	cap = app_config.attribute("framerate_cap").as_int(-1);

	if (cap > 0)
	{
		capped_ms = 1000 / cap;
	}

	if (ret == true)
	{
		p2List_item<j1Module*>* item;
		item = modules.start;

		while (item != NULL && ret == true)
		{
			ret = item->data->Awake(config.child(item->data->name.GetString()));
			item = item->next;
		}
	}

	return ret;
}

// Called before the first frame
bool j1App::Start()
{
	bool ret = true;
	p2List_item<j1Module*>* item;
	item = modules.start;

	while (item != NULL && ret == true)
	{
		if(item->data->active == true)
			ret = item->data->Start();

		item = item->next;
	}
	startup_time.Reset();

	return ret;
}

// Called each loop iteration
bool j1App::Update()
{
	BROFILER_CATEGORY("AppUpdate", Profiler::Color::Blue);

	bool ret = true;
	PrepareUpdate();

	if (input->GetWindowEvent(WE_QUIT) == true)
		ret = false;

	if (ret == true)
		ret = PreUpdate();

	if (ret == true)
		ret = DoUpdate();

	if (ret == true)
		ret = PostUpdate();

	FinishUpdate();
	return ret;
}

// ---------------------------------------------
pugi::xml_node j1App::LoadConfig(pugi::xml_document& config_file) const
{
	pugi::xml_node ret;

	pugi::xml_parse_result result = config_file.load_file("config.xml");

	if (result == NULL)
		LOG("Could not load map xml file config.xml. pugi error: %s", result.description());
	else
		ret = config_file.child("config");

	return ret;
}

// ---------------------------------------------
void j1App::PrepareUpdate()
{
	frame_count++;
	last_sec_frame_count++;

	dt = frame_time.ReadSec();
	frame_time.Reset();
}

// ---------------------------------------------
void j1App::FinishUpdate()
{
	if (want_to_save == true)
		SavegameNow();

	if (want_to_load == true)
		LoadGameNow();

	// Framerate calculations --

	if (last_sec_frame_time.Read() > 1000)
	{
		last_sec_frame_time.Reset();
		prev_last_sec_frame_count = last_sec_frame_count;
		last_sec_frame_count = 0;
	}

	float avg_fps = float(frame_count) / startup_time.ReadSec();
	float seconds_since_startup = startup_time.ReadSec();
	uint32 last_frame_ms = frame_time.Read();
	uint32 frames_on_last_update = prev_last_sec_frame_count;

	static char title[256];
	sprintf_s(title, 256, "Av.FPS: %.2f Last Frame Ms: %u Last sec frames: %i Last dt: %.3f Time since startup: %.3f Frame Count: %lu ",
		avg_fps, last_frame_ms, frames_on_last_update, dt, seconds_since_startup, frame_count);
	App->win->SetTitle(title);

	if (capped_ms > 0 && last_frame_ms < capped_ms)
	{
		j1PerfTimer t;
		SDL_Delay(capped_ms - last_frame_ms);
		LOG("We waited for %d milliseconds and got back in %f", capped_ms - last_frame_ms, t.ReadMs());
	}
}

// Call modules before each loop iteration
bool j1App::PreUpdate()
{
	BROFILER_CATEGORY("PreUpdate", Profiler::Color::Blue);

	bool ret = true;
	p2List_item<j1Module*>* item;
	item = modules.start;
	j1Module* pModule = NULL;

	for (item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if (pModule->active == false) {
			continue;
		}

		ret = item->data->PreUpdate();
	}

	return ret;
}

// Call modules on each loop iteration
bool j1App::DoUpdate()
{
	BROFILER_CATEGORY("Update", Profiler::Color::Blue);
	bool ret = true;
	p2List_item<j1Module*>* item;
	item = modules.start;
	j1Module* pModule = NULL;

	for (item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if (pModule->enabled == false) {
			continue;
		}

		ret = item->data->Update(dt);
	}

	return ret;
}

// Call modules after each loop iteration
bool j1App::PostUpdate()
{
	BROFILER_CATEGORY("PostUpdate", Profiler::Color::Blue);
	bool ret = true;
	p2List_item<j1Module*>* item;
	j1Module* pModule = NULL;

	for (item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if (pModule->enabled == false) {
			continue;
		}

		ret = item->data->PostUpdate();
	}

	return ret;
}

// Called before quitting
bool j1App::CleanUp()
{
	bool ret = true;
	p2List_item<j1Module*>* item;
	item = modules.end;

	while (item != NULL && ret == true)
	{
		ret = item->data->CleanUp();
		item = item->prev;
	}

	return ret;
}

// ---------------------------------------
int j1App::GetArgc() const
{
	return argc;
}

// ---------------------------------------
const char* j1App::GetArgv(int index) const
{
	if (index < argc)
		return args[index];
	else
		return NULL;
}

// ---------------------------------------
const char* j1App::GetTitle() const
{
	return title.GetString();
}

float j1App::GetDT() const
{
	return dt;
}

// ---------------------------------------
const char* j1App::GetOrganization() const
{
	return organization.GetString();
}

// Load / Save
void j1App::LoadGame(const char* file)
{
	// we should be checking if that file actually exist
	// from the "GetSaveGames" list
	want_to_load = true;
	load_game.create(file);
}

// ---------------------------------------
void j1App::SaveGame(const char* file) const
{
	// we should be checking if that file actually exist
	// from the "GetSaveGames" list ... should we overwrite ?

	want_to_save = true;
	save_game.create(file);
}

// ---------------------------------------


bool j1App::LoadGameNow()
{
	bool ret = false;

	pugi::xml_document data;
	pugi::xml_node root;

	pugi::xml_parse_result result = data.load_file(load_game.GetString());

	if (result != NULL)
	{
		LOG("Loading new Game State from %s...", load_game.GetString());

		root = data.child("game_state");

		p2List_item<j1Module*>* item = modules.start;
		ret = true;

		while (item != NULL && ret == true)
		{
			ret = item->data->Load(root.child(item->data->name.GetString()));
			item = item->next;
		}

		data.reset();
		if (ret == true)
			LOG("...finished loading");
		else
			LOG("...loading process interrupted with error on module %s", (item != NULL) ? item->data->name.GetString() : "unknown");
	}
	else
		LOG("Could not parse game state xml file %s. pugi error: %s", load_game.GetString(), result.description());

	want_to_load = false;
	return ret;
}

bool j1App::SavegameNow() const
{
	bool ret = true;

	LOG("Saving Game State to %s...", save_game.GetString());

	// xml object were we will store all data
	pugi::xml_document data;
	pugi::xml_node root;

	root = data.append_child("game_state");

	p2List_item<j1Module*>* item = modules.start;

	while (item != NULL && ret == true)
	{
		ret = item->data->Save(root.append_child(item->data->name.GetString()));
		item = item->next;
	}

	if (ret == true)
	{
		data.save_file(save_game.GetString());	
		LOG("... finished saving", save_game.GetString());
	}
	else
		LOG("Save process halted from an error in module %s", (item != NULL) ? item->data->name.GetString() : "unknown");

	data.reset();
	want_to_save = false;
	return ret;
}