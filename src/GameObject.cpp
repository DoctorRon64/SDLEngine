#include "GameObject.h"
#include <cassert>
#include <SDL3_image/SDL_image.h>
#include "Engine.h"

GameObject::GameObject(std::string texturePath, SDL_Renderer* renderer)
{
	texture = IMG_LoadTexture(renderer, texturePath.c_str());
	assert(texture != nullptr && "Failed to load texture");

	position = Vector2();
	destinationRect = { position.x, position.y, (float)texture->w, (float)texture->h };
	sourceRect = { position.x, position.y, (float)texture->w, (float)texture->h };
}

GameObject::~GameObject()
{
	//dispose
}

void GameObject::SetPosition(Vector2 newPos)
{
	position = newPos;
	destinationRect.x = position.x;
	destinationRect.y = position.y;
}

void GameObject::Update()
{
}

void GameObject::Render(SDL_Renderer* renderer)
{
	SDL_RenderTexture(renderer, texture, &sourceRect, &destinationRect);
}