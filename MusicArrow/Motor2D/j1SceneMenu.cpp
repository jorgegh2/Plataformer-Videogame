#include "j1App.h"
#include "j1Input.h"
#include "j1FadeToBlack.h"
#include "j1Gui.h"
#include "j1SceneMenu.h"
#include "j1Fonts.h"
#include "j1Scene_Forest.h"

j1SceneMenu::j1SceneMenu()
{
	name.create("j1SceneMenu");
}


//Destructor
j1SceneMenu::~j1SceneMenu() {}

bool j1SceneMenu::Awake(pugi::xml_node& node)
{
	//App->map->Load(node.child("bgmusic").child("level2").attribute("source").as_string());
	return true;
}



// Called before the first frame
bool j1SceneMenu::Start()
{
	//App->map->Load("Level2.tmx");

	//Menu UI elements
	_TTF_Font* font = App->font->Load("fonts/kenvector_future/kenvector_future.ttf");
	SDL_Rect rects[3] = { { 438,497,392,102 },{ 1305,497,392,102 },{ 2172,497,392,102 } };
	playButton = App->gui->CreateButton({ 1250,200 }, rects, "Play", { 255, 255, 255, 255 }, font);
	continueButton = App->gui->CreateButton({ 1250,400 }, rects, "Continue", { 255, 255, 255, 255 }, font);
	settingsButton = App->gui->CreateButton({ 1250,600 }, rects, "Settings", { 255, 255, 255, 255 }, font);
	creditsButton = App->gui->CreateButton({ 1250,800 }, rects, "Credits", { 255, 255, 255, 255 }, font);
	exitButton = App->gui->CreateButton({ 1250,1000 }, rects, "Exit", { 255, 255, 255, 255 }, font);

	//Settings elements
	//panel = App->gui->
	return true;
}

// Called each loop iteration
bool j1SceneMenu::Update(float dt)
{
	if (playButton->GetEvent() == MouseLeftClickEvent)
	{
		App->fadeToBlack->FadeToBlack(this, App->map_forest);
	}

	if (exitButton->GetEvent() == MouseLeftClickEvent)
	{
		return false;
	}

	if (playButton->GetEvent() == MouseLeftClickEvent)
	{
		App->fadeToBlack->FadeToBlack(this, App->map_forest);
	}

	return true;
}

bool j1SceneMenu::CleanUp()
{
	App->gui->CleanUp();
	return true;
}
