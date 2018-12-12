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
bool j1Gui::PreUpdate()
{
	for (item = GuiEntities.start; item; item = item->next)
	{
		item->data->PreUpdate();
	}
	return true;
}

//// Called after all Updates
//bool j1Gui::PostUpdate()
//{
//	return true;
//}

bool j1Gui::Update(float dt)
{

	for (item = GuiEntities.start; item; item = item->next)
	{
		item->data->Update(dt);
	}


	for (item = GuiEntities.start; item; item = item->next)
	{
		item->data->Draw(item->data->GetUITexture());
	}

	DrawAll();
	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");
	App->tex->UnLoad(atlas);

	item = GuiEntities.start;
	while (item != nullptr)
	{
		RELEASE(item->data);
		item = item->next;
	}
	GuiEntities.clear();

	return true;
}

// const getter for atlas
SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}


void j1Gui::DrawAll() 
{
	for (item = GuiEntities.start; item; item = item->next)
	{
		item->data->Draw(item->data->GetUITexture());
	}
}

void j1Gui::CreateImage(iPoint position, SDL_Rect rectImage)
{
	
	UIImage* entity = new UIImage(position, rectImage);
	GuiEntities.add(entity);
	
}

void j1Gui::CreateLabel(iPoint position, p2SString text, SDL_Color color, _TTF_Font* font)
{

	UILabel* entity = new UILabel(position, text, color, font);
	GuiEntities.add(entity);

}

void j1Gui::CreateButton(iPoint position, SDL_Rect rectToDraw[], p2SString text, SDL_Color color, _TTF_Font* font)
{
	UIButton* entity = new UIButton(position, rectToDraw, text, color, font);
	GuiEntities.add(entity);

}



// class Gui ---------------------------------------------------

