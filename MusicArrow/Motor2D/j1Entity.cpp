#include "j1App.h"
#include "j1Entity.h"
#include "j1Collision.h"
#include "j1Render.h"
#include "j1Audio.h"
#include "j1Textures.h"
#include "SDL/include/SDL_rect.h"

Entity::Entity(int x, int y) : position(x, y)
{

}

bool Entity::Awake(pugi::xml_node& config)
{
	return true;
}

Entity::~Entity()
{
	if (collider != nullptr)
		collider->to_delete = true;

}

const Collider* Entity::GetCollider() const
{
	return collider;
}

void Entity::Draw(SDL_Texture* sprites)
{
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);


	if (animation != nullptr) {
		SDL_Rect aux = animation->GetCurrentFrame();
		App->render->Blit(sprites, position.x, position.y, &(animation->GetCurrentFrame()));
	}
}


void Entity::OnCollision(Collider* collider)
{

}
