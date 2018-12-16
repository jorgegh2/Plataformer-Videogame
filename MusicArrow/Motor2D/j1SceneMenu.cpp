#include "j1App.h"
#include "j1Input.h"
#include "j1FadeToBlack.h"
#include "j1Gui.h"
#include "j1SceneMenu.h"
#include "j1Fonts.h"
#include "j1Scene_Forest.h"
#include "j1Scene_Winter.h"
#include "j1Textures.h"
#include "j1Render.h"

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

	//Settings elements 3091,61
	panel = App->gui->CreateImage({ 500,400 }, { 3028,4,528, 653 });
	music = App->gui->CreateLabel({ 570, 450 }, "Music:", {255,255,255,255}, font);
	fx = App->gui->CreateLabel({ 570, 550 }, "Fx:", { 255,255,255,255 }, font);
	musicSlider = App->gui->CreateSlider({ 570, 494 }, { 1738,650,394,11 }, {1738,687,17,17});
	fxSlider = App->gui->CreateSlider({ 570, 594 }, { 1738,650,394,11 }, { 1738,687,17,17 });

	panel->SetParentAndChildren(music);
	panel->SetParentAndChildren(fx);
	panel->SetParentAndChildren(musicSlider);
	panel->SetParentAndChildren(fxSlider);
	panel->ChangeEnabled();

	////App->map->Load("Level2.tmx");

	////Menu UI elements
	//_TTF_Font* font = App->font->Load("fonts/kenvector_future/kenvector_future.ttf");
	//SDL_Rect rects[3] = { { 438,497,392,102 },{ 1305,497,392,102 },{ 2172,497,392,102 } };
	//playButton = App->gui->CreateButton({ 600,150 / 2 }, rects, "Play", { 255, 255, 255, 255 }, font);
	//continueButton = App->gui->CreateButton({ 600,400 / 2 }, rects, "Continue", { 255, 255, 255, 255 }, font);
	//settingsButton = App->gui->CreateButton({ 600 ,650 / 2 }, rects, "Settings", { 255, 255, 255, 255 }, font);
	//creditsButton = App->gui->CreateButton({ 600,900 / 2 }, rects, "Credits", { 255, 255, 255, 255 }, font);
	//exitButton = App->gui->CreateButton({ 600,1150 / 2 }, rects, "Exit", { 255, 255, 255, 255 }, font);

	////Settings elements 3091,61
	//panel = App->gui->CreateImage({ 25,50 }, { 3028,4,528, 653 });
	//music = App->gui->CreateLabel({ 75, 100 }, "Music:", { 255,255,255,255 }, font);
	//fx = App->gui->CreateLabel({ 75, 150 }, "Fx:", { 255,255,255,255 }, font);
	//musicSlider = App->gui->CreateSlider({ 75, 125 }, { 1738,650,394,11 }, { 1738,687,17,17 });
	//fxSlider = App->gui->CreateSlider({ 75, 175 }, { 1738,650,394,11 }, { 1738,687,17,17 });

	//panel->SetParentAndChildren(music);
	//panel->SetParentAndChildren(fx);
	//panel->SetParentAndChildren(musicSlider);
	//panel->SetParentAndChildren(fxSlider);
	//panel->ChangeEnabled();

	bg = App->tex->Load("gui/BG.png");
	bgRect = { App->render->camera.x, App->render->camera.y, App->render->camera.w * 2, App->render->camera.h * 2 };
	return true;
}

// Called each loop iteration
bool j1SceneMenu::Update(float dt)
{
	
	App->render->Blit(bg, 0, 0, &bgRect);
	if (playButton->GetEvent() == MouseLeftClickEvent)
	{
		App->fadeToBlack->FadeToBlack(this, App->map_forest);
	}

	if (exitButton->GetEvent() == MouseLeftClickEvent)
	{
		return false;
	}

	if (settingsButton->GetEvent() == MouseLeftClickEvent)
	{
		panel->ChangeEnabled();
	}

	return true;
}

bool j1SceneMenu::CleanUp()
{
	App->gui->CleanUp();
	return true;
}
