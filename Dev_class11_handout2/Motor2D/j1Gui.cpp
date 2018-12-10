#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
//#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"

j1Gui::j1Gui() : j1Module()
{
	name.create("gui");

	for (uint i = 0; i < MAX_GUI_ENTITIES; ++i)
	{
		GuiEntities[i] = nullptr;
	}
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = App->tex->Load(atlas_file_name.GetString());

	return true;
}

// Update all guis
//bool j1Gui::PreUpdate()
//{
//	return true;
//}
//
//// Called after all Updates
//bool j1Gui::PostUpdate()
//{
//	return true;
//}

bool j1Gui::Update(float dt)
{
	for (uint i = 0; i < MAX_GUI_ENTITIES; i++)
	{
		GuiEntities[i]->Update(dt);
	}

	Draw();
	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");

	for (uint i = 0; i < MAX_GUI_ENTITIES; ++i)
	{
		if (GuiEntities[i] != nullptr)
		{
			delete GuiEntities[i];
			GuiEntities[i] = nullptr;
		}
	}

	return true;
}

// const getter for atlas
const SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}


void j1Gui::Draw() const
{
	for (uint i = 0; i < MAX_GUI_ENTITIES; i++)
	{
		if (GuiEntities[i] != nullptr)
		{
			GuiEntities[i]->Draw(atlas);
		}
	}
}

void j1Gui::CreateImage(iPoint position, SDL_Rect rectImage)
{
	for (uint i = 0; i < MAX_GUI_ENTITIES; i++)
	{
		if (GuiEntities[i] == nullptr)
		{
			GuiEntities[i] = new UIImage(position, rectImage);
			break;
		}
	}
}

void j1Gui::CreateLabel(iPoint position, p2SString text, SDL_Color color, _TTF_Font* font)
{
	for (uint i = 0; i < MAX_GUI_ENTITIES; i++)
	{
		if (GuiEntities[i] == nullptr)
		{
			GuiEntities[i] = new UILabel(position, text, color, font);
			break;
		}
	}
}



// class Gui ---------------------------------------------------

