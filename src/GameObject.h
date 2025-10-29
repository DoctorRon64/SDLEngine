#pragma once
#include "Vector2.h"
#include <SDL3/SDL_render.h>
#include <string>
class GameObject
{
protected:
	Vector2 position;
	SDL_Texture* texture;
	SDL_FRect sourceRect;
	SDL_FRect destinationRect;

public:
	GameObject(std::string texturePath, SDL_Renderer* renderer);
	~GameObject();

	void SetPosition(Vector2 pos);
	Vector2 GetPosition() const {
		return position;
	}

	void Update();
	void Render(SDL_Renderer* renderer);
};