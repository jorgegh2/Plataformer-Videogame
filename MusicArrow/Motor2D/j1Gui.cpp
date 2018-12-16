#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
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
		if (item->data->isEnabled)
		{
			item->data->PreUpdate();

			for (p2List_item<UIElement*>* item2 = item->data->listChildren.start; item2; item2 = item2->next)
			{
				if (item2->data->isEnabled)
				{
					item2->data->PreUpdate();
				}
			}
		}
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
		if (item->data->isEnabled)
		{
			item->data->Update(dt);
			for (p2List_item<UIElement*>* item2 = item->data->listChildren.start; item2; item2 = item2->next)
			{
				if (item2->data->isEnabled)
				{
					item2->data->Update(dt);
				}
			}
		}
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
		if (item->data->isEnabled)
		{
			item->data->Draw(item->data->GetUITexture());
		}
	}
}

UIImage* j1Gui::CreateImage(iPoint position, SDL_Rect rectImage, bool dragable)
{
	UIImage* entity = new UIImage(position, rectImage, dragable);
	GuiEntities.add(entity);
	return entity;
}

UILabel* j1Gui::CreateLabel(iPoint position, p2SString text, SDL_Color color, _TTF_Font* font, bool dragable)
{
	UILabel* entity = new UILabel(position, text, color, font, dragable);
	GuiEntities.add(entity);
	return entity;
}

UIButton* j1Gui::CreateButton(iPoint position, SDL_Rect rectToDraw[], p2SString text, SDL_Color color, _TTF_Font* font, bool dragable)
{
	UIButton* entity = new UIButton(position, rectToDraw, text, color, font, dragable);
	GuiEntities.add(entity);
	return entity;
}

UIBoxText* j1Gui::CreateBoxText(iPoint position, SDL_Rect rectImage, p2SString text, SDL_Color color, _TTF_Font* font, bool dragable)
{
	UIBoxText* entity = new UIBoxText(position, rectImage, text, color, font, dragable);
	GuiEntities.add(entity);
	return entity;
}

UISlider* j1Gui::CreateSlider(iPoint position, SDL_Rect barImageRect, SDL_Rect zamImageRect, bool dragable)
{
	UISlider* entity = new UISlider(position, barImageRect, zamImageRect, dragable);
	GuiEntities.add(entity);
	return entity;
}