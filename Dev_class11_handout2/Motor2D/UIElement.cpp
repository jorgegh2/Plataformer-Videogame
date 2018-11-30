#include "j1App.h"
#include "GuiEntity.h"
#include "j1Render.h"
#include "p2Log.h"


void GuiEntity::Draw(SDL_Texture* atlas) const
{
	if (type == IMAGE)
	{
		if (!App->render->Blit(atlas, position.x, position.y, &Image))
		{
			LOG("ERROR to blit a Gui Entity!");
		}
	}
}